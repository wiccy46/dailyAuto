This is for git automati 
This is another one that is really good to type on.

```
mkdir build

cmake -S . -B build -DCMAKE_EXPORT_COMPILE_COMMANDS=YES -DCMAKE_BUILD_TYPE=Release

cd build

conan install ..

cmake --build .
```

Then you can link compile_commands by: 

At root dir: `ls -s build/compile_commands.json`