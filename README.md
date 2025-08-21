# 🎯 Dotify

**Dotify** is a sleek image-processing application that transforms almost any image file into a dot-printed version — perfect for artistic effects, retro visuals, or minimalist printing. It supports a wide range of formats including `.jpg`, `.png`, `.bmp`, `.tiff`, and more.

## 🧭 Platform Compatibility

- ✅ **Linux** (fully supported)  
- ⚙️ **Windows** (currently in development)

## 🚀 How to Use

### 🔧 Installation via `.deb` Package

Download the provided `.deb` package and install it using:

```bash
sudo dpkg -i dotify_1.0-1.deb
```

Then, from a terminal just run
```bash
Dotify
```

### 🔧 Manual compilation

```bash
git clone https://github.com/yourusername/dotify.git
cd dotify
mkdir build && cd build
cmake ..
make
```
Once compiled, you can run Dotify from the build directory.

Notice that, in Linux, the paths to the images can be absolute or relative

## 📦 Project Status

Dotify is under active development. Linux is fully supported, and Windows compatibility is planned for future releases.

## 🤝 Contributing

Contributions are welcome! Feel free to fork the repository, create a feature branch, and submit a pull request. Bug reports, feature suggestions, and general feedback are also appreciated.
