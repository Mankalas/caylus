#!/bin/sh

# This script is used to update all references with new outputs. This
# script may be used when the test output has changed but the
# significance of the test hasn't (same players' moves, same resources
# spent...)

REFERENCES=`find . -name ref`

for ref in $REFERENCES; do
		ref_path=`dirname $ref`
		cp $ref_path/output $ref_path/ref
done
