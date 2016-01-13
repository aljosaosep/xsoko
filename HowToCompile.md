# How to compile on (Ubuntu) Linux? #

  1. install netbeans
  1. checkout (sdl brach)
  1. install zlib
  1. install boost (including signals and filesystem modules)
  1. install sdl (with image and mixer module)
  1. install ftgl and, at least in Ubuntu Linux 8.10 and higher, use next hack: "sudo ln -s /usr/include/freetype2/ freetype /usr/include/freetype")
  1. compile and you're done

# Dependencies (Linux) #

  * libftgl-dev
  * libboost-signals-dev
  * libsdl-dev
  * libsdl-image-dev
  * libsage-dev