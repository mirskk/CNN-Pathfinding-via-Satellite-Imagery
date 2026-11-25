# CNN-Pathfinding-via-Satellite-Imagery
Developing a machine learning pipeline using a CNN with C++ to process satellite imagery and detect optimal navigation paths across rough terrain. No external ML libraries used in the process.

# Rough Terrain Pathfinding CNN (C++ From Scratch)

A Convolutional Neural Network (CNN) built **from scratch in C++ without external machine learning libraries**, designed to analyze satellite imagery and identify optimal navigation paths across rough terrain. Includes a Python GUI utility for dataset organization and preprocessing.

> **Status:** Active Development — Core convolutional, pooling, activation, and flattening layers are implemented; currently finalizing the dense layer before starting model training.

---

## Project Architecture

```
pathfinding_cnn/
├── gui/
│   └── gui.py                     -> Python GUI for dataset labeling, naming & organization
├── layer_logic/
│   ├── Tensor.h                   -> Custom multi-dimensional tensor representation
│   ├── FilterBank.h               -> Kernel/filter storage and management
│   ├── ImageProcessingInitial.*   -> Image loading (stb_image) & initial preprocessing
│   ├── convolution.* / convolution1.* -> Custom 2D convolutional layers
│   ├── ReLU.*                     -> ReLU activation functions
│   ├── maxPool1.* - maxPool8.*    -> Max-pooling layers & spatial dimension reduction
│   ├── Flattening.*               -> Tensor-to-1D vector flattening
│   ├── denseLayer.*               -> Fully connected dense layer (in progress)
│   └── main.cpp                   -> Forward-pass pipeline & dimension tracking
└── DEV_LOG.txt                    -> Development progress & debugging log
```

---

## Key Features & Implementation Details

* **Zero External ML Frameworks:** All tensor structures, filter banks, convolutions, pooling operations, and activations are written manually in C++ using only `stb_image.h` for raw pixel ingestion.
* **Spatial Dimension Tracking:** Tracks and validates tensor shrinkage across successive convolution and max-pooling stages directly in the console.
* **Dataset Preprocessing GUI:** Built a Python interface (`gui.py`) to standardize image file naming and organize satellite terrain samples into structured training directories.

---

## Roadmap

- [x] Image ingestion & initial preprocessing (`stb_image.h`)
- [x] Custom `Tensor` and `FilterBank` data structures
- [x] Convolutional, ReLU, and Max-Pooling layer implementations
- [x] Python GUI for dataset organization
- [ ] Finalize 1D resizing & fully connected `denseLayer`
- [ ] Implement backpropagation & train on satellite terrain dataset
- [ ] Integrate path probability visualization into the GUI

