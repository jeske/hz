@rm -f target\stdout.log
cd target
hz -w
cd ..
tail target\stdout.log
