# NeuroProbe
  A Performance Profiling Feed Forward Neural Network Simulator for Hardware Interaction Analysis

## 📌 Overview
This repository contains a **NeuroProbe** for compilation and execution. This repository also contains a menu-driven Bash script, which automatically runs performance benchmarking with **Likwid** and ensures proper cleanup after execution.


## 📂 Repository Structure
```
.
├── run_neuroprobe.sh    # Main menu-driven script
├── Makefile.withGEMM_withAVX
├── Makefile.withGEMM_withAVX_SSE4.2
├── Makefile.withGEMM_withoutSIMD
├── Makefile.withGEMM_withSSE4.2
├── Makefile.withoutGEMM_withAVX
├── Makefile.withoutGEMM_withAVX_SSE4.2
├── Makefile.withoutGEMM_withoutSIMD
├── Makefile.withoutGEMM_withSSE4.2
├── bin/                 # Directory for compiled executables
└── src/                 # Source code directory
```


---

## 📥 Dependencies
Before running the script, ensure you have installed the required tools.

### 1️⃣ **Install GCC and Make**
```sh
sudo apt-get install build-essential
```

### 2️⃣ **Install Likwid Benchmarking Tool**
```sh
sudo apt-get install likwid
```
For other Linux distributions, follow the official instructions at:  
🔗 [Likwid GitHub Repository](https://github.com/RRZE-HPC/likwid)

---

## 📌 SIMD Optimization Table
| Version | SIMD Support |
|---------|-------------|
| **WithoutSIMD** | No SIMD optimization |
| **SSE** | Enabled with SSE4.2 optimizations |
| **AVX** | Uses AVX instructions for better vectorization |
| **AVX SSE** | Combines AVX and SSE4.2 for enhanced performance |

---

---

## 📌 Makefile Details
| Makefile | GEMM Computation | SIMD Optimization |
|----------|----------------|-------------------|
| Makefile.withGEMM_withAVX | Enabled | AVX |
| Makefile.withGEMM_withAVX_SSE4.2 | Enabled | AVX + SSE4.2 |
| Makefile.withGEMM_withoutSIMD | Enabled | None |
| Makefile.withGEMM_withSSE4.2 | Enabled | SSE4.2 |
| Makefile.withoutGEMM_withAVX | Disabled | AVX |
| Makefile.withoutGEMM_withAVX_SSE4.2 | Disabled | AVX + SSE4.2 |
| Makefile.withoutGEMM_withoutSIMD | Disabled | None |
| Makefile.withoutGEMM_withSSE4.2 | Disabled | SSE4.2 |

---

## ⚡ How to Use the Script
### 1️⃣ **Clone the Repository**
```sh
git clone https://github.com/yourusername/neuroprobe.git
cd neuroprobe
```

### 2️⃣ **Give Execution Permission**
```sh
chmod +x runscript.sh
```

### 3️⃣ **Run the Script**
```sh
./runscript.sh
```

---

## 📌 Menu Options
When you run the script, you will see:

```
==================================================
⚠️  ALERT: Ensure you have installed Likwid benchmarking tool before proceeding!
   If not installed, run: sudo apt-get install likwid (Debian/Ubuntu)
   For other distros, visit: https://github.com/RRZE-HPC/likwid
==================================================
=====================================
      NeuroProbe Build Menu          
=====================================
1. Makefile.withGEMM_withAVX
2. Makefile.withGEMM_withAVX_SSE4.2
3. Makefile.withGEMM_withoutSIMD
4. Makefile.withGEMM_withSSE4.2
5. Makefile.withoutGEMM_withAVX
6. Makefile.withoutGEMM_withAVX_SSE4.2
7. Makefile.withoutGEMM_withoutSIMD
8. Makefile.withoutGEMM_withSSE4.2
0. Exit
=====================================
Enter your choice (0-8): 
```

---

## 🛠️ Compilation & Execution Process

### 4️⃣ **Select a Makefile**
- Enter a number between **1 and 8** to choose a **Makefile**.
- Example:
  ```
  Enter your choice (0-8): 2
  ```

### 5️⃣ **Compilation Process**
- The script will **clean, compile, and build** the project using the selected **Makefile**.

### 6️⃣ **Running Likwid Benchmarking**
Once compiled, the script will **automatically execute**:

```sh
sudo likwid-perfctr -C S0:0 -g MEM_DP bin/neuroprobe
```
This command:
- Runs **Likwid Performance Counters** on **Core 0**.
- Monitors **Memory Data Path (MEM_DP) metrics**.

### 7️⃣ **Memory Cleanup with Likwid**
```sh
sudo likwid-memsweeper
```
This ensures that memory is cleaned after execution.

---

## ❓ Troubleshooting
| Issue | Solution |
|--------|---------|
| `Command 'likwid' not found` | Ensure Likwid is installed using `sudo apt-get install likwid`. |
| `Permission denied` | Run `chmod +x run_neuroprobe.sh` before execution. |
| `Compilation failed` | Check the Makefile syntax and ensure all dependencies are installed. |
| `Invalid choice` | Enter a number between 0-8 when selecting a Makefile. |

---

## 📜 License
This project is **open-source** and distributed under the **MIT License**.

---
