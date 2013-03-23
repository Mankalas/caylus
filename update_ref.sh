#!/bin/sh

# This script is used to update all references with new outputs. This
# script may be used when the test output has changed but the
# significance of the test hasn't (same players' moves, same resources
# spent...)

OUTPUTS=`find . -name output`

for output in $OUTPUTS; do
		output_path=`dirname $output`
		cp $output_path/output $output_path/ref
done
