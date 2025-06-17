# 📘 MTE 140 - Assignments & Resources

This repository is created for **MTE 140** assignments and related resources.


## 📂 Repository Structure

You can generate the directory structure using the following command:

```bash
find . -print | sed -e 's;[^/]*/;│   ;g;s;│   \([^│]\);├── \1;' 
```

All assignment code files should be placed under the `src/assignments/` directory. **Do not modify files outside of this directory** unless explicitly instructed.


## 🛠️ Development Guidelines

### 🧪 Compiling & Testing
- The compiled file **must be named `main.cpp`** for proper pipeline validation.
- You may use the [fff](https://github.com/meekrosoft/fff) framework for unit testing (especially useful for math logic), although it is **not** integrated into the pipeline yet.


### 🌿 Branching Strategy
- Create your own feature branch for each assignment using the following naming convention:
1. assignments: a# -- name
    - example: a1 -- alice
2. lab questions/practice questions: lab# -- name
    - example: lab2 -- bob


### ✅ Pull Request Rules
- Always open a Pull Request (PR) to merge changes into `main`.
- Each PR **requires 2 approvals** before it can be merged.


## ✅ Quick Checklist Before PR

- [ ] Code is in `src/`
- [ ] File is named `main.cpp`
- [ ] Branch follows naming convention
- [ ] Code builds and runs locally or containerized environment 





# 🚀 Steps to Set Up Docker Container

## 🐳 Setting Up the Docker Dev Container

Follow these steps to build and open the development container using **Visual Studio Code Dev Containers**:


### 🔧 Prerequisites

Make sure you have the following installed:

- [Docker](https://www.docker.com/)
- [Visual Studio Code](https://code.visualstudio.com/)
- [Remote - Containers Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)


### 🚀 Getting Started

1. **Clone the repository**:

   ```bash
   git clone https://github.com/SAT-oO/MTE_140.git
   cd your-repo-name
   ``` 

2. 🖥️ **Open in VS Code**

    Launch **Visual Studio Code** and open the cloned folder.


3.  🔄 **Reopen in Container**

    Press `F1` (or `Cmd+Shift+P` on macOS), then run:

        Dev Containers: Reopen in Container


    VS Code will automatically build the image using the `.devcontainer/devcontainer.json` file and start the container environment.


