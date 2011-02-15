#!/usr/bin/env bash

rsync -rv --exclude=.svn --delete ./ io_alex_2004,mp3splt@web.sourceforge.net:/home/groups/m/mp/mp3splt/htdocs/repository/

