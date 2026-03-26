# Key Logger Project 🔐

## Essence 💡

Welcome to my Key Logger project! This repository houses a fundamental key logger designed specifically for Windows environments. By delving into this project, you'll gain insight into the intriguing world of key logging techniques and their implications.

To better understand the concept of a key logger and its potential applications, consider exploring this concise resource: [What is a keylogger?](https://www.malwarebytes.com/keylogger)

## Ethical Guidelines 🤝

This project adheres to a set of ethical principles:

- **Education Priority:** This project is an educational resource intended to enhance understanding within the realm of key logging.
- **Non-Malicious Intent:** Key Logger must not be employed for malicious purposes, invasion of privacy, or any unethical activities.
- **Legal Compliance:** Users must comply with legal regulations and obtain proper authorization before testing this tool on any system.

## Getting Started 🚀

### Prerequisites 📚

- Windows 10 or later
- [Git](https://git-scm.com/downloads)
- [Build Tools for Visual Studio](https://visualstudio.microsoft.com/visual-cpp-build-tools/) (MSVC + Windows SDK + NMake)

Clone this repository

```
git clone https://github.com/Ami-hub/Keylogger.git
```

Go to the `Keylogger` directory

```
cd Keylogger
```

Build and run the project 
```
nmake run
``` 

**Important:** Use `nmake` on Windows (comes with Visual Studio). Do **not** use `make` (Unix-like), as it conflicts with the MSVC compiler flags.


## Usage 📝

After running the project, the key logger will begin recording keystrokes.  
By default, the key logger saves the recorded keystrokes `output.keys.txt` file in the `Keylogger` directory.

## Screenshots 📸
<p align="center">
  <img src="https://github.com/Ami-hub/Keylogger/assets/57874729/c979cfaf-3779-40cd-8540-f0e3d475a0eb" alt="App Screenshot" width="80%" />
</p>

## License 📜

Feel free to use, modify, and distribute my Key Logger project without any restrictions. For more information, see [Unlicence](https://github.com/Ami-hub/Keylogger/blob/master/LICENSE).  
Embrace the spirit of freedom and collaboration! 🌐🔓
