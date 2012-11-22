/**********************************************************
 *
 * audacity.c -- Audacity label file parser portion of the Mp3Splt utility
 *                    Utility for mp3/ogg splitting without decoding
 *
 * Copyright (c) 2002-2004 M. Trotta - <matteo.trotta@lib.unimib.it>
 * Copyright (c) 2007 Federico Grau - <donfede@casagrau.org>
 * Copyright (c) 2010-2012 Alexandru Munteanu <m@ioalex.net>
 *
 * http://mp3splt.sourceforge.net
 * http://audacity.sourceforge.net/
 */

/**********************************************************
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307,
 * USA.
 *
 *********************************************************/

/*!\file 

Manages a socket connection
*/

#include <unistd.h>

#ifdef __WIN32__
#include <conio.h>
#include <winsock.h>
#else
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#include <string.h>

#include "splt.h"
#include "socket_manager.h"

#define SPLT_BUFFER_SIZE 1024
#define SPLT_MAXIMUM_NUMBER_OF_LINES_READ 1000

static char *get_message_decorated_with_http(splt_socket_handler *sh, const char *message,
    splt_state *state);
static char *get_message_with_proxy(splt_socket_handler *sh, const char *message, splt_state *state);
static char *get_message_without_proxy(splt_socket_handler *sh, const char *message);
static int message_starts_with_get(const char *message);

void splt_sm_connect(splt_socket_handler *sh, const char *hostname, int port, splt_state *state)
{
  const char *real_hostname = hostname;
  int real_port = port;
  if (splt_pr_has_proxy(state))
  {
    real_hostname = splt_pr_get_proxy_address(state);
    real_port = splt_pr_get_proxy_port(state);
  }

  splt_d_print_debug(state, "\nConnecting on host %s:%d\n", real_hostname, real_port);

  struct hostent *host_entity = NULL;
  
  int err = splt_su_copy(hostname, &sh->hostname);
  if (err < 0) { sh->error = err; return; }

#ifdef __WIN32__
  WSADATA winsock;
  long winsockinit = WSAStartup(0x0101,&winsock);
  if (winsockinit != 0)
  {
    splt_e_set_strerror_msg(state);
    sh->error = SPLT_FREEDB_ERROR_INITIALISE_SOCKET;
    return;
  }
#endif

  host_entity = gethostbyname(real_hostname);

  if (host_entity == NULL)
  {
    splt_e_set_strherror_msg(state);
    splt_e_set_error_data(state, real_hostname);
    sh->error = SPLT_FREEDB_ERROR_CANNOT_GET_HOST;
    return;
  }

  struct sockaddr_in my_socket;
  memset(&my_socket, 0x0, sizeof(my_socket));
  my_socket.sin_family = AF_INET;
  my_socket.sin_addr.s_addr = ((struct in_addr *) (host_entity->h_addr)) ->s_addr;
  my_socket.sin_port = htons(real_port);

  sh->fd = socket(AF_INET, SOCK_STREAM, 0);
  if (sh->fd == -1)
  {
    splt_e_set_strerror_msg(state);
    sh->error = SPLT_FREEDB_ERROR_CANNOT_OPEN_SOCKET;
    return;
  }

  if (connect(sh->fd, (void *)&my_socket, sizeof(my_socket)) < 0)
  {
    splt_e_set_strerror_msg(state);
    splt_e_set_error_data(state, real_hostname);
    sh->error = SPLT_FREEDB_ERROR_CANNOT_CONNECT;
    return;
  }

  splt_d_print_debug(state, " ... connected.\n");
}

void splt_sm_send(splt_socket_handler *sh, const char *message, 
    splt_state *state)
{
  splt_d_print_debug(state, "\nSending message _%s_\n", message);

  if (send(sh->fd, message, strlen(message), 0) == -1)
  {
    splt_e_set_strerror_msg(state);
    splt_e_set_error_data(state, sh->hostname);
    sh->error = SPLT_FREEDB_ERROR_CANNOT_SEND_MESSAGE;
  }

  splt_d_print_debug(state, " ... message sent.\n");
}

void splt_sm_send_http_message(splt_socket_handler *sh, const char *message,
    splt_state *state)
{
  char *message_with_http = get_message_decorated_with_http(sh, message, state);
  if (message_with_http == NULL)
  {
    return;
  }

  splt_sm_send(sh, message_with_http, state);

  if (message_with_http)
  {
    free(message_with_http);
    message_with_http = NULL;
  }
}

static char *get_message_decorated_with_http(splt_socket_handler *sh, const char *message,
    splt_state *state)
{
  if (splt_pr_has_proxy(state) && message_starts_with_get(message))
  {
    return get_message_with_proxy(sh, message, state);
  }

  return get_message_without_proxy(sh, message);
}

static int message_starts_with_get(const char *message)
{
  if (strlen(message) < 4)
  {
    return SPLT_FALSE;
  }

  if (message[0] == 'G' && message[1] == 'E' && message[2] == 'T' && message[3] == ' ')
  {
    return SPLT_TRUE;
  }

  return SPLT_FALSE;
}

static char *get_message_with_proxy(splt_socket_handler *sh, const char *message, 
    splt_state *state)
{
  char *message_with_proxy = NULL;
  int err = splt_su_append_str(&message_with_proxy, 
      "GET http://", sh->hostname, message + 4, " HTTP/1.0\r\n",
      "UserAgent: ", SPLT_PACKAGE_NAME, "/", SPLT_PACKAGE_VERSION, "\r\n",
      "Host: ", sh->hostname, NULL);
  if (err < 0) { sh->error = err; return NULL; }

  if (splt_pr_has_proxy_authentification(state))
  {
    splt_su_append_str(&message_with_proxy, 
        "\r\nProxy-Authorization: Basic ",
        splt_pr_get_proxy_authentification(state), NULL);
    if (err < 0)
    { 
      sh->error = err;
      free(message_with_proxy);
      return NULL;
    }
  }

  splt_su_append_str(&message_with_proxy, "\r\n\r\n", NULL);
  if (err < 0)
  {
    sh->error = err;
    free(message_with_proxy);
    return NULL;
  }

  return message_with_proxy;
}

static char *get_message_without_proxy(splt_socket_handler *sh, const char *message)
{
  char *message_with_http = NULL;
  int err = splt_su_append_str(&message_with_http, 
      message, " HTTP/1.0\r\nHost: ", sh->hostname, "\r\n\r\n", NULL);
  if (err < 0) { sh->error = err; return NULL; }

  return message_with_http;
}

int splt_sm_process_without_headers_functor(const char *received_line, 
    int line_number, void *user_data)
{
  splt_sm_functor_decorator *sm_fd = (splt_sm_functor_decorator *) user_data;
 
  if (!sm_fd->processing_headers)
  {
    int real_line_number = 
      sm_fd->line_number_after_headers - sm_fd->num_lines_to_skip;

    if (real_line_number > 0)
    {
      int we_continue = sm_fd->functor(received_line, real_line_number, sm_fd->user_data);
      if (!we_continue)
      {
        return SPLT_FALSE;
      }
    }
    sm_fd->line_number_after_headers++;
  }

  if (strlen(received_line) == 0)
  {
    sm_fd->processing_headers = SPLT_FALSE;
  }

  return SPLT_TRUE;
}

char *splt_sm_receive_and_process_without_headers_with_recv(splt_socket_handler *sh, 
    splt_state *state,
    ssize_t (*recv_func)(int fd, void *buf, size_t len, int flags),
    int (*process_functor)(const char *received_line, int line_number, void *user_data),
    void *user_data, int number_of_lines_to_skip_after_headers)
{
  splt_sm_functor_decorator *sm_fd = malloc(sizeof(splt_sm_functor_decorator));
  if (!sm_fd)
  {
    sh->error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
    return;
  }

  sm_fd->functor = process_functor;
  sm_fd->user_data = user_data;
  sm_fd->processing_headers = SPLT_TRUE;
  sm_fd->num_lines_to_skip = number_of_lines_to_skip_after_headers;
  sm_fd->line_number_after_headers = 1;
  sm_fd->line_number = 1;

  char *first_line = splt_sm_receive_and_process_with_recv(sh, state, 
      recv_func, splt_sm_process_without_headers_functor, sm_fd);

  free(sm_fd);
  sm_fd = NULL;

  return first_line;
}

char *splt_sm_receive_and_process_without_headers(splt_socket_handler *sh, 
    splt_state *state, 
    int (*process_functor)(const char *received_line, int line_number, void *user_data),
    void *user_data, int number_of_lines_to_skip_after_headers)
{
  return splt_sm_receive_and_process_without_headers_with_recv(sh, state, recv,
      process_functor, user_data, number_of_lines_to_skip_after_headers);
}

void splt_sm_receive_and_process(splt_socket_handler *sh, splt_state *state,
    int (*process_functor)(const char *received_line, int line_number, void *user_data),
    void *user_data)
{
  char *first_line = 
    splt_sm_receive_and_process_with_recv(sh, state, recv, process_functor, user_data);

  if (first_line)
  {
    free(first_line);
  }
}

char *splt_sm_receive_and_process_with_recv(splt_socket_handler *sh, splt_state *state,
    ssize_t (*recv_func)(int fd, void *buf, size_t len, int flags),
    int (*process_functor)(const char *received_line, int line_number, void *user_data),
    void *user_data)
{
  splt_d_print_debug(state, "\nWaiting for response ...");

  int err = SPLT_OK;
  char *first_line = NULL;

  char *lines = NULL;

  char *remaining_line = NULL;
  int remaining_line_size = 0;

  char buffer[SPLT_BUFFER_SIZE] = { '\0' };

  int number_of_lines_read = 0;

  char *line_begin = NULL;
  char *line_end = NULL;

  int line_number = 1;

  while (number_of_lines_read < SPLT_MAXIMUM_NUMBER_OF_LINES_READ) {
    memset(buffer, '\0', SPLT_BUFFER_SIZE);
#ifdef __WIN32__
    int received_bytes = recv(sh->fd, buffer, SPLT_BUFFER_SIZE, 0);
#else
    int received_bytes = recv_func(sh->fd, buffer, SPLT_BUFFER_SIZE, 0);
#endif
    if (received_bytes == -1)
    {
      splt_e_set_strerror_msg(state);
      splt_e_set_error_data(state, sh->hostname);
      sh->error = SPLT_FREEDB_ERROR_CANNOT_RECV_MESSAGE;
      goto end;
    }

    if (received_bytes == 0)
    {
      break;
    }

    err = splt_su_set(&lines, remaining_line, remaining_line_size, NULL);
    if (err < 0) { sh->error = err; goto end; }

    err = splt_su_append(&lines, buffer, received_bytes, NULL);
    if (err < 0) { sh->error = err; goto end; }

    remaining_line_size += received_bytes;

    if (!lines)
    {
      continue;
    }

    line_begin = lines;
    line_end = NULL;

    while ((line_end = strchr(line_begin, '\n')) != NULL)
    {
      int line_size = (line_end - line_begin) + 1;

      char *line = NULL;
      err = splt_su_set(&line, line_begin, line_size, "\0", 1, NULL);
      if (err < 0) { sh->error = err; goto end; }

      splt_su_line_to_unix(line);
      splt_su_str_cut_last_char(line);

      splt_d_print_debug(state, "Received line _%s_\n", line);

      if (line_number == 1)
      {
        err = splt_su_copy(line, &first_line);
        if (err < 0) { sh->error = err; goto end; }
      }

      int we_continue = process_functor(line, line_number, user_data);

      line_number++;

      if (line)
      {
        free(line);
        line = NULL;
      }

      if (!we_continue)
      {
        goto end;
      }

      remaining_line_size -= line_size;
      line_begin = line_end + 1;
    }

    err = splt_su_set(&remaining_line, line_begin, remaining_line_size, NULL);
    if (err < 0) { sh->error = err; goto end; }
  }

end:
  if (lines)
  {
    free(lines);
    lines = NULL;
  }
  if (remaining_line)
  {
    free(remaining_line);
    remaining_line = NULL;
  }

  return first_line;
}

void splt_sm_close(splt_socket_handler *sh, splt_state *state)
{
  if (closesocket(sh->fd) == -1)
  {
    splt_e_set_strerror_msg(state);
    sh->error = SPLT_FREEDB_ERROR_CANNOT_DISCONNECT;
  }

#ifdef __WIN32__
  WSACleanup();
#endif
}

splt_socket_handler *splt_sm_socket_handler_new(int *error)
{
  splt_socket_handler *sh = malloc(sizeof(splt_socket_handler));
  if (sh == NULL)
  {
    *error = SPLT_ERROR_CANNOT_ALLOCATE_MEMORY;
    return NULL;
  }
  memset(sh, 0x0, sizeof(splt_socket_handler));

  sh->error = SPLT_OK;
  sh->hostname = NULL;

  return sh;
}

void splt_sm_socket_handler_free(splt_socket_handler **sh)
{
  if (!sh || !*sh)
  {
    return;
  }

  if ((*sh)->hostname)
  {
    free((*sh)->hostname);
    (*sh)->hostname = NULL;
  }

  free(*sh);
  *sh = NULL;
}

