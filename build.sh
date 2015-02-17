for folder in script editor plugin tests examples; do
  echo Building $folder
  cd $folder
  . compile.sh
  cd ..
  echo Done
done
