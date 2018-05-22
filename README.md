# Tempus

Tempus is a library to generate temporary files / directories.

This library is cross-platform and work om UNIX and Windows.

```cpp
#include <tempus.h>

std::string dir_name = tempus::tmpDir();
std::string file_name = tempus::tmpFile();
```

# License

This library is provided under the MIT License
