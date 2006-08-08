#!/usr/bin/env bash

rsync -rv --exclude=.svn --delete ./ io_alex_2004@shell.sf.net:/home/groups/m/mp/mp3splt/htdocs/mp3splt_page/
