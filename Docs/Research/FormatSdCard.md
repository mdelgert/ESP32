winget install Ridgecrop.guiformat
run gui guiformat

for command
winget install Ridgecrop.fat32format

https://fat32format-gui.en.lo4d.com/windows

Formatting an SD card larger than 64GB as FAT32 can be challenging because most operating systems don't offer FAT32 as a formatting option for drives larger than 32GB by default. Here's how you can achieve it:

---

### **Windows**

1. **Use a Third-Party Tool**
   Download and use a tool like [GUIFormat (FAT32 Format)](http://ridgecrop.co.uk/index.htm?guiformat.htm) to format the SD card.

   - Download the tool and run it (no installation needed).
   - Select your SD card from the list.
   - Choose **FAT32** as the file system.
   - Click **Start** to format.

2. **Using Command Prompt (PowerShell)**
   If you prefer a built-in method:
   ```powershell
   format /FS:FAT32 X:
   ```
   Replace `X:` with the drive letter of your SD card. This method works only for cards up to 32GB, but third-party tools are required for larger cards.

---

### **Linux**

1. **Using `mkfs`**
   Open a terminal and run the following commands:

   - Identify the SD card:
     ```bash
     lsblk
     ```
   - Format the SD card as FAT32:
     ```bash
     sudo mkfs.fat -F 32 /dev/sdX
     ```
     Replace `/dev/sdX` with the correct device name (e.g., `/dev/sdb`).

2. **Using `gparted` (GUI)**
   - Install `gparted`:
     ```bash
     sudo apt install gparted
     ```
   - Open `gparted` and select your SD card.
   - Create a new partition table (`msdos`) if required.
   - Format the partition as FAT32.

---

### **macOS**

1. **Using Disk Utility**
   - Open **Disk Utility**.
   - Select the SD card.
   - Erase the card and choose **MS-DOS (FAT)** as the file system and **Master Boot Record (MBR)** as the scheme.

2. **Using Terminal**
   - Identify the SD card:
     ```bash
     diskutil list
     ```
   - Unmount the card:
     ```bash
     diskutil unmountDisk /dev/diskX
     ```
     Replace `/dev/diskX` with the correct device name.
   - Format the card as FAT32:
     ```bash
     sudo newfs_msdos -F 32 /dev/diskX
     ```

---

### Notes:
- **ExFAT vs. FAT32**: FAT32 has a file size limit of 4GB per file. If you don't need FAT32 specifically, consider using exFAT, which is widely supported and doesn't have the 4GB file size limitation.
- **Back up your data**: Formatting will erase all data on the SD card.
- Ensure your SD card is not write-protected before formatting.
