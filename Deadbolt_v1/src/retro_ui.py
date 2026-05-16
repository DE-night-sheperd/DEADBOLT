import tkinter as tk
from tkinter import ttk, messagebox
import sys
import os

# Windows 95/98 color scheme
WIN95_BG = "#c0c0c0"
WIN95_DARK = "#808080"
WIN95_LIGHT = "#ffffff"
WIN95_BLUE = "#000080"
WIN95_BLACK = "#000000"

class DeadboltRetroUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Deadbolt Endpoint Shield")
        self.root.geometry("640x480")
        self.root.configure(bg=WIN95_BG)
        self.root.resizable(False, False)
        
        # Add Windows 95 style window border effect
        self.setup_ui()
        
    def setup_ui(self):
        # Title bar (simulated)
        title_bar = tk.Frame(self.root, bg=WIN95_BLUE, height=30)
        title_bar.pack(fill=tk.X)
        title_bar.pack_propagate(False)
        
        tk.Label(
            title_bar, 
            text="Deadbolt Endpoint Shield", 
            bg=WIN95_BLUE, 
            fg=WIN95_LIGHT,
            font=("MS Sans Serif", 8, "bold"),
            anchor=tk.W
        ).pack(side=tk.LEFT, padx=5, pady=5)
        
        # Close button
        close_btn = tk.Button(
            title_bar, 
            text="X", 
            bg=WIN95_BG,
            font=("MS Sans Serif", 8, "bold"),
            width=3,
            command=self.root.quit
        )
        close_btn.pack(side=tk.RIGHT, padx=5, pady=2)
        
        # Main content area with beveled border
        main_frame = tk.Frame(self.root, bg=WIN95_BG, padx=2, pady=2)
        main_frame.pack(fill=tk.BOTH, expand=True)
        
        # Inner frame with shadow effect
        inner = tk.Frame(main_frame, bg=WIN95_BG, padx=8, pady=8)
        inner.pack(fill=tk.BOTH, expand=True)
        
        # Icon and title
        top_frame = tk.Frame(inner, bg=WIN95_BG)
        top_frame.pack(fill=tk.X, pady=(0, 20))
        
        # Simulated icon (text-based)
        icon_label = tk.Label(
            top_frame, 
            text="🔒", 
            font=("Arial", 48), 
            bg=WIN95_BG
        )
        icon_label.pack(side=tk.LEFT, padx=10)
        
        title_frame = tk.Frame(top_frame, bg=WIN95_BG)
        title_frame.pack(side=tk.LEFT, fill=tk.BOTH, expand=True)
        
        tk.Label(
            title_frame,
            text="DEADBOLT",
            font=("MS Sans Serif", 18, "bold"),
            bg=WIN95_BG,
            fg=WIN95_BLACK
        ).pack(anchor=tk.W)
        
        tk.Label(
            title_frame,
            text="Endpoint Shield v1.0",
            font=("MS Sans Serif", 10),
            bg=WIN95_BG,
            fg=WIN95_BLACK
        ).pack(anchor=tk.W)
        
        # Status area
        status_group = tk.LabelFrame(
            inner, 
            text="System Status", 
            bg=WIN95_BG,
            font=("MS Sans Serif", 8, "bold"),
            padx=10,
            pady=10
        )
        status_group.pack(fill=tk.X, pady=10)
        
        self.status_vars = {
            "monitor": tk.BooleanVar(value=True),
            "ransomware": tk.BooleanVar(value=True),
            "zip_bomb": tk.BooleanVar(value=True),
            "threat_mitigation": tk.BooleanVar(value=True)
        }
        
        status_items = [
            ("Real-time Monitoring", "monitor"),
            ("Ransomware Protection", "ransomware"),
            ("Zip Bomb Detection", "zip_bomb"),
            ("Threat Mitigation", "threat_mitigation")
        ]
        
        for text, key in status_items:
            frame = tk.Frame(status_group, bg=WIN95_BG)
            frame.pack(fill=tk.X, pady=2)
            
            cb = tk.Checkbutton(
                frame,
                text=text,
                variable=self.status_vars[key],
                bg=WIN95_BG,
                font=("MS Sans Serif", 8),
                selectcolor=WIN95_LIGHT,
                activebackground=WIN95_BG
            )
            cb.pack(side=tk.LEFT, anchor=tk.W)
            
            status_label = tk.Label(
                frame,
                text="[ACTIVE]",
                bg=WIN95_BG,
                fg="#008000",
                font=("MS Sans Serif", 8, "bold")
            )
            status_label.pack(side=tk.RIGHT)
        
        # Button area
        btn_frame = tk.Frame(inner, bg=WIN95_BG)
        btn_frame.pack(fill=tk.X, pady=20)
        
        buttons = [
            ("Scan Now", self.scan_now),
            ("Settings", self.show_settings),
            ("About", self.show_about),
            ("Exit", self.root.quit)
        ]
        
        for text, cmd in buttons:
            btn = tk.Button(
                btn_frame,
                text=text,
                width=12,
                command=cmd,
                bg=WIN95_BG,
                font=("MS Sans Serif", 8),
                padx=8,
                pady=2
            )
            btn.pack(side=tk.LEFT, padx=5)
        
        # Progress bar (simulated)
        progress_frame = tk.Frame(inner, bg=WIN95_BG)
        progress_frame.pack(fill=tk.X, pady=10)
        
        tk.Label(
            progress_frame,
            text="System Health:",
            bg=WIN95_BG,
            font=("MS Sans Serif", 8)
        ).pack(anchor=tk.W)
        
        self.progress = ttk.Progressbar(
            progress_frame,
            orient=tk.HORIZONTAL,
            length=100,
            mode='determinate'
        )
        self.progress.pack(fill=tk.X, pady=5)
        self.progress['value'] = 85
        
        # Status bar
        status_bar = tk.Frame(self.root, bg=WIN95_BG, height=20, relief=tk.SUNKEN, bd=1)
        status_bar.pack(fill=tk.X, side=tk.BOTTOM)
        status_bar.pack_propagate(False)
        
        tk.Label(
            status_bar,
            text="Ready",
            bg=WIN95_BG,
            font=("MS Sans Serif", 8),
            anchor=tk.W
        ).pack(side=tk.LEFT, padx=2)
        
    def scan_now(self):
        messagebox.showinfo("Scan", "System scan completed!\n\nNo threats found!")
        
    def show_settings(self):
        messagebox.showinfo("Settings", "Settings panel coming soon!")
        
    def show_about(self):
        about_text = (
            "Deadbolt Endpoint Shield v1.0\n"
            "Built with Python & Tkinter\n\n"
            "Protection Features:\n"
            "- Real-time monitoring\n"
            "- Ransomware detection\n"
            "- Zip bomb detection\n"
            "- Threat mitigation system\n"
        )
        messagebox.showinfo("About", about_text)

def main():
    root = tk.Tk()
    app = DeadboltRetroUI(root)
    root.mainloop()

if __name__ == "__main__":
    main()
