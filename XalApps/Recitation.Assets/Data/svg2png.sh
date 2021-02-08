#!/bin/bash
for i in {1..114}
do
 inkscape --export-type="png" -w 256 -h 256 $i.svg
done
