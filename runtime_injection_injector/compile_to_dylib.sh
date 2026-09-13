clang++ -dynamiclib util/payload.cpp \
    -std=c++20 \
    -I/opt/homebrew/include \
    -L/opt/homebrew/lib \
    -lglfw \
    -o payload/payload.dylib