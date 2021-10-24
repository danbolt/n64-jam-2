#!/bin/bash


echo "#ifndef AUTOGENERATED_SFX_IDS_HEADER"
echo "#define AUTOGENERATED_SFX_IDS_HEADER"

echo ""
echo ""

count=0
for i in compressed/*.aifc; do
  nm=${i#compressed/}
  name=${nm%.aifc}

  echo "/* $nm  */"

  sfxdefine="#define SFX_${name^^} $count"
  echo ${sfxdefine}
  echo ""

  count=$((count+1))
done


echo ""
echo "#endif"