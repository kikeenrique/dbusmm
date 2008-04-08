#!/bin/bash

function autocmd()
{
	echo "Running ${1}..."
	$* || {
		echo "Error running ${1}"
		exit 1
	}
}

autocmd libtoolize --force --copy
autocmd aclocal
autocmd autoheader
# -Wportability skips non-POSIX variable name
autocmd automake --add-missing --force-missing --gnu --copy --warnings=all
autocmd autoconf

echo "Autogen done, now you can ./configure"
