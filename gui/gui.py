import customtkinter as ctk
import tkinter
import tkintermapview
from tkinter import ttk
from tkinter import *
from PIL import ImageGrab
import math
import pyscreenshot
import os
import datetime
from pathlib import Path

class Application(ctk.CTk):
    def __init__(self):
        super().__init__()

        self.title("My app")
        self.geometry("1280x720")
        # self.resizable(False, False) - somehow it still resizes

        #Grids
        self.grid_columnconfigure(0, weight=0)
        self.grid_columnconfigure(1, weight=0)
        self.grid_columnconfigure(2, weight=1)
        self.grid_columnconfigure(3, weight=0)
        self.grid_columnconfigure(4, weight=0)

        self.grid_rowconfigure(0, weight=0)
        self.grid_rowconfigure(1, weight=1)

        self.sliderbtn()
        self.levellbls()
        self.centerc()
        self.sidebar_right()

        self.after(200, self.update_zoom_metric)


    def sliderbtn(self):

        #Help btn
        self.buttonhelp = ctk.CTkButton(
            self, 
            text="?", 
            text_color="#6e1e02",
            fg_color="#fa865c", 
            hover_color="#6a8cf0",
            width=40, 
            height=40,
            corner_radius=20,
            border_spacing=0,
            command=self.popup_for_info
        )
        self.buttonhelp.grid(row=0, column=0, padx=10, pady=10)

        # Slider tracking frame
        self.slider_track_frame = ctk.CTkFrame(self, fg_color="#fa865c", width=50, height=500, corner_radius=10)
        self.slider_track_frame.grid(row=1, column=0, padx=5, pady=10, sticky="e")
        self.slider_track_frame.grid_propagate(False)

        # Slider itself
        self.slider = ctk.CTkSlider(master=self.slider_track_frame,
            width=10,
            height=400,
            from_=1,
            to=4,
            number_of_steps=3,
            progress_color="#6a8cf0",
            button_color="white",
            button_hover_color="grey",
            orientation="vertical",
            border_width=0
        )
        self.slider.place(relx=0.5, rely=0.5, anchor="center")

    def levellbls(self):
        # levels next to slider
        self.frameTFS = ctk.CTkFrame(
            self,
            height=500,
            width=130,
            corner_radius=0
        )
        self.frameTFS.grid(
            row=1, 
            column=1, 
            padx=0, 
            pady=0, 
            sticky="w"
        )
        self.frameTFS.grid_propagate(False)
        #kitty stepped on keyboard
        #dssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssssseexxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxlokokokokokokokokokokokokokokokokokokokokokokokppppppppppppppppppppppppppppppppppppppp';[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu9io]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
        levels = ["Adventurer", "Advanced", "Intermediate", "Beginner"]
        for i, leveltxt in enumerate(levels):
            self.frameTFS.grid_rowconfigure(i, weight=1)

            tfs = ctk.CTkLabel(
                master=self.frameTFS,
                text=leveltxt,
                font=ctk.CTkFont(family="Times New Roman", size=20),
                anchor="w"
            )
            tfs.grid(row=i, column=1, padx=(15, 0), sticky="w")
        
        self.unlockbtn = ctk.CTkButton(
            self,
            height=40,
            width=50,
            corner_radius=10,
            text="Unlock Adventurer mode",
            font=ctk.CTkFont(family="Times New Roman", size=14),
            text_color="#6e1e02",
            fg_color="#fa865c", 
            hover_color="#6a8cf0",
            border_spacing=0,
            command=self.popup_warn
        )
        self.unlockbtn.grid(row=3, column=1, padx=5, pady=5, sticky="nsew")

    def centerc(self):
        #Big label frame above all
        self.frameforlabel = ctk.CTkFrame(
            self,
            fg_color="#fa865c",
            height=70,
            width=500
        )
        self.frameforlabel.grid(row=0, column=2, padx=10, pady=10, sticky="ew")
        self.frameforlabel.grid_propagate(False)

        #Label itself
        self.label = ctk.CTkLabel(
            master=self.frameforlabel, 
            text="App development for adventure-seekers", 
            fg_color="#fa865c",
            height=40,
            width=100,
            font=ctk.CTkFont(family="Times New Roman", size=23, weight="bold"),
            text_color="#6e1e02"
        )
        self.label.place(relx=0.5, rely=0.5, anchor="center")

        #Map containing frame
        self.frameformap = ctk.CTkFrame(
            self,
            fg_color="#fa865c",
            height=1280,
            width=720,
            border_width=5,
            border_color="#fa5c24"
        )
        self.frameformap.grid(row=1, column=2, padx=20, pady=20, sticky="nsew")

        #Map view itself
        self.map_container = ctk.CTkFrame(
            self,
            fg_color="#fa865c",
            height=1280,
            width=720,
            border_width=5,
            border_color="#fa5c24"
        )
        self.map_container.grid(row=1, column=2, padx=20, pady=20) #, sticky="nsew"
        self.map_container.pack_propagate(False)

        self.map_widget = tkintermapview.TkinterMapView(self.map_container, corner_radius=0)
        self.map_widget.set_tile_server("https://mt0.google.com/vt/lyrs=s&hl=en&x={x}&y={y}&z={z}&s=Ga", max_zoom=22)
        # self.map_widget.set_overlay_tile_server("http://a.tiles.openrailwaymap.org/standard/{z}/{x}/{y}.png")
        self.map_widget.pack(fill="both", expand=True, padx=20, pady=20)
        self.map_widget.set_position(42.48043, 23.32418)
        self.map_widget.set_zoom(15)

        # Bind squish mechanic // commented out because i want to lock the resolution in
        # self.map_container.bind("<Configure>", self.on_map_resize)

        self.map_widget.canvas.bind("<MouseWheel>", lambda e: self.after(50, self.update_zoom_metric), add="+")
        self.map_widget.canvas.bind("<ButtonRelease-1>", lambda e: self.update_zoom_metric(), add="+")

    #Handles squishy window for resizing // commented out because i want to lock the resolution in
    # def on_map_resize(self, event):
    #     self.map_container.configure(
    #         width=event.width - 40, 
    #         height=event.height - 40
    #     )
    def sidebar_right(self):
        # Little button upper right
        self.button2 = ctk.CTkButton(
            self, 
            text="Отзиви", 
            text_color="#6e1e02",
            fg_color="#fa865c", 
            hover_color="#6a8cf0",
            width=40, 
            height=40,
            corner_radius=20,
            border_spacing=0,
            command=self.popup
        )
        self.button2.grid(row=0, column=3, padx=10, pady=10)

        #frame for text label right of the map
        self.right_side_container = ctk.CTkFrame(
            self,
            fg_color="transparent",
            width=280
        )
        self.right_side_container.grid(row=1, column=3, padx=10, pady=10, sticky="nsew")
        # self.right_side_container.grid_propagate(False)

        self.right_side_container.grid_columnconfigure(0, weight=1)
        self.right_side_container.grid_rowconfigure(0, weight=1)
        self.right_side_container.grid_rowconfigure(1, weight=0)

        self.frametext = ctk.CTkFrame(
            master=self.right_side_container,
            corner_radius=10
        )
        self.frametext.grid(
            row=1, 
            column=3, 
            padx=10, 
            pady=(0, 10), 
            sticky="nsew")
        # self.frametext.grid_propagate(False)
        self.frametext.grid_columnconfigure(0, weight=1)
        self.frametext.grid_rowconfigure(0, weight=1)

        self.textFT = ctk.CTkLabel(
            master=self.frametext,
            text="Loading map data...", 
            font=ctk.CTkFont(family="Times New Roman", size=17),
            wraplength=250,
            anchor="nw",
            text_color="white",
            justify="left"
        )
        self.textFT.grid(row=1, column=3, padx=15, pady=15, sticky="nsew")

        self.searchbtn = ctk.CTkButton(
            master=self.right_side_container,
            height=60,
            width=200,
            corner_radius=10,
            text="Search area",
            font=ctk.CTkFont(family="Times New Roman", size=18),
            text_color="#6e1e02",
            fg_color="#fa865c", 
            hover_color="#6a8cf0",
            border_spacing=0,
            command=self.capture_screen
        )
        self.searchbtn.grid(row=2, column=3, padx=10, pady=10, sticky="nsew")

    def update_zoom_metric(self, event=None):
        lat, lng = self.map_widget.get_position()
        zoom = self.map_widget.zoom
        
        meters_per_px = (156543.03392*math.cos(math.radians(lat))) / (2**zoom)
        
        self.update_idletasks()  # update gui
        frame_h = self.map_widget.canvas.winfo_height()
        if frame_h <= 1: 
            frame_h = 500
            
        total_meters = frame_h * meters_per_px
        
        self.textFT.configure(text=f"Current location:\n"
                                f"Latitude: {lat:.5f}\n"
                                f"Longitude: {lng:.5f}\n\n\n"
                                f"Zoom Level: {zoom}\n\n"
                                f"Span top-to-bottom:\n"
                                f"~{total_meters:.2f} meters.\n\n"
                                f"TIP: Zooming in 1 level cuts this\n"
                                f"distance exactly in half!\n\n\n", 
                                font=ctk.CTkFont(family="Times New Roman", size=18)        
                                )
    # image saving function
    def capture_adjust(self, image):
        pics_dir = Path(__file__).resolve().parent.parent / "pics"
        pics_dir.mkdir(parents=True, exist_ok=True)

        self.update_zoom_metric()
        coords = self.map_widget.get_position()
        lat, lng = coords
        zoom = self.map_widget.zoom
        zoom_idx = float(zoom)
        timestamp = datetime.datetime.now(datetime.timezone.utc).strftime("%d-%m-%Y_%H-%M-%S")
        filename = f"{lat:.6f}_{lng:.6f}_{timestamp}_{zoom_idx:.2f}.png"

        save_path = pics_dir / filename
        image.save(save_path)
        print(f"Satellite map snapshot saved cleanly to: {save_path}")

    def popup(self):
        popup = ctk.CTkToplevel(self)
        popup.title("popup")
        popup.geometry("400x220")

        popup.lift()
        popup.attributes("-topmost", True)

        popup.grid_columnconfigure(0, weight=1)
        popup.grid_rowconfigure(0, weight=1)

        frm = ctk.CTkFrame(popup, corner_radius=10)
        frm.grid(padx=15, pady=15, sticky="nsew")

        ttxx = ctk.CTkLabel(frm, text="Nothing here yet?")
        ttxx.grid(row=0, column=0, pady=10)

        bt = ctk.CTkButton(frm, text="Complain", command=popup.destroy, fg_color="#fa865c", text_color="#6e1e02")
        bt.grid(row=1, column=0, pady=5)

    def popup_for_info(self):
        popup = ctk.CTkToplevel(self)
        popup.title("Information for program usage")
        popup.geometry("400x400")

        popup.lift()
        popup.attributes("-toolwindow", True)

        frm2 = ctk.CTkFrame(popup, corner_radius=10)
        frm2.grid(padx=15, pady=15, sticky="nsew")

        txx = ctk.CTkLabel(frm2, text="Welcome to the Information tab.\n"
                                    "Here you can learn how to use the program.\n\n"
                                    "NOTE: Adventurer mode is locked, unless you explicitly\n"
                                    "click on the 'Unlock Adventurer mode' button below the\n"
                                    "slidebar.\n\n"
                                    "If you'd like to contribute, report an issue, or flag\n"
                                    "an existing error, you can click the 'Report' tab in\n"
                                    "the upper right corner of the page.\n\n"
                                    "Zooming in via the buttons gives a more predictable zoom\n"
                                    "number in the quantifier, which would get the clearest\n"
                                    "results, in comparison to the mouse scroll button.\n\n"
                                    )
        txx.grid(row=0, column=1, pady=10, sticky="n")

        btt = ctk.CTkButton(frm2, text="Done", command=popup.destroy, fg_color="#fa865c", text_color="#6e1e02")
        btt.grid(row=1, column=1, padx=5, pady=5)

    def popup_warn(self):
        popup = ctk.CTkToplevel(self)
        popup.title("Warning")
        popup.geometry("600x300")

        popup.lift()
        popup.attributes("-alpha", True)

#nbbbbb hhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhhh90
        popup.grid_columnconfigure(0, weight=1)
        frm = ctk.CTkFrame(popup, corner_radius=10)
        frm.grid(padx=15, pady=15, sticky="nsew")

        frm.grid_columnconfigure(0, weight=1)
        frm.grid_columnconfigure(1, weight=1)
        frm.grid_rowconfigure(0, weight=1)
        frm.grid_rowconfigure(1, weight=0)

        ttxx = ctk.CTkLabel(frm, text="Warning: Adventurer mode consists of\n"
                                        "paths that have scored a probability"
                                        "of close to 60%. This can include: \n"
                                        "- unexpected elevation/denivelation;\n"
                                        "- unexpected cliff encounters;\n"
                                        "- long-gone paths OR no path at all;\n\n"
                                        "By agreeing to have read this message, \n"
                                        "you consent to the possibility of an \n"
                                        "unwalkable route.\n",
                                        font=ctk.CTkFont(family="Times New Roman", size=16)
                                        )
        ttxx.grid(row=0, column=0, columnspan=2, pady=10, sticky="n")

        bt = ctk.CTkButton(frm, text="Agree", command=popup.destroy, fg_color="#fa865c", text_color="#6e1e02")
        bt.grid(row=1, column=0, padx=10, pady=(0,10), sticky="e")

        bt = ctk.CTkButton(frm, text="Disagree", command=popup.destroy, fg_color="#fa865c", text_color="#6e1e02")
        bt.grid(row=1, column=1, padx=10, pady=(0,10), sticky="w")

    def capture_screen(self):
        self.update_idletasks()

        logical_x1 = self.map_widget.winfo_rootx()
        logical_y1 = self.map_widget.winfo_rooty()
        logical_w  = self.map_widget.winfo_width()
        logical_h  = self.map_widget.winfo_height()

        scaling_factor = ctk.ScalingTracker.get_window_scaling(self)

        x1 = int(logical_x1 * scaling_factor)
        y1 = int(logical_y1 * scaling_factor)
        x2 = int((logical_x1 + logical_w) * scaling_factor)
        y2 = int((logical_y1 + logical_h) * scaling_factor)

        print(f"Capturing bounding box coordinates: ({x1}, {y1}) to ({x2}, {y2})")
        print(f"Vector: x {x2-x1} y {y2-y1}")
        image = pyscreenshot.grab(bbox=(x1, y1, x2, y2))
        self.capture_adjust(image)

if __name__ == "__main__":
    app = Application()
    app.mainloop()
