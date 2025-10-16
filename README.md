# c-image-processing
A command-line application written in C to perform image processing operations on BMP files.
---

## ⚙️ Supported Operations

| # | Operation | Description |
|---|------------|--------------|
| 1  | Seuillage | Applies binary thresholding to the image. |
| 2  | Symétrie | Creates a vertical or horizontal symmetry. |
| 3  | Bordure | Highlights or draws borders around objects. |
| 4  | Rotation 90 | Rotates the image by 90°. |
| 5  | Contraste | Adjusts image contrast. |
| 6  | Filtre Médian | Applies a median filter to reduce noise. |
| 7  | LUT1 | Applies the first lookup table transformation. |
| 8  | LUT2 | Applies the second lookup table transformation. |
| 9  | Agrandissement | Enlarges the image. |
| 10 | Caractéristiques Image | Displays image characteristics (dimensions, bit depth, etc.). |
| 11 | Négatif | Inverts all colors. |
| 12 | Niveaux de Gris | Converts the image to grayscale. |
| 13 | Miroir | Flips the image horizontally. |
| 14 | Monochrome | Converts to black & white. |
| 15 | Réduction | Reduces the image size. |
| 16 | Histogramme | Generates and displays the histogram. |
| 17 | Augmenter Luminosité | Increases image brightness. |
| 18 | Inversion | Performs pixel inversion (color or orientation). |

---

##  Usage

1. **Compile the program**
   ```bash
   gcc main.c -o c-processing-image
   ```
2. **Run it**
```bash
./c-processing-image
```
3. **Follow the on-screen menu**

Notes:

- Only BMP format is supported.

- Built entirely in C, with no external dependencies.

- The interface makes it easy to explore classic image processing operations interactively.

- Designed for educational use and experimentation with basic image algorithms.

- You can see some results in the 
