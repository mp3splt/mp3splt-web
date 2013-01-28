#!/bin/sh

dir=$1

versions="squeeze wheezy unstable oneiric precise quantal"

for version in $versions;do
  echo "processing $version ..."
  changes_files=$(ls $dir/*${version}*.changes)
  for changes_file in $changes_files;do
    reprepro -b . include $version $changes_file
  done
done

echo "done"

