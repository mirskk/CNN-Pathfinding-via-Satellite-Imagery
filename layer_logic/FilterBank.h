#pragma once
#include <vector>

namespace FilterBank {
    using Filter3D = std::vector<std::vector<std::vector<float>>>;
    // --- LAYER 3 FILTERS
    //a T turn
    inline const Filter3D layer3_turnT = {
        { { -1.0f, 2.0f, -1.0f, -1.0f },  { -1.0f, 2.0f, -1.0f, -1.0f },  { -1.0f, 2.0f, -1.0f, -1.0f } },
        { { -1.0f, -1.0f, -1.0f, -1.0f },  { 2.0f, -1.0f, -1.0f, -1.0f },  { -1.0f, -1.0f, -1.0f, -1.0f } },
        { { -1.0f, -1.0f, -1.0f, -1.0f },  { 2.0f, -1.0f, -1.0f, -1.0f },  { -1.0f, -1.0f, -1.0f, -1.0f } }
    };
    //a reverse T turn
    inline const Filter3D layer3_turnTrev = {
        { { -1.0f, -1.0f, -1.0f, -1.0f },  { 2.0f, -1.0f, -1.0f, -1.0f },  { -1.0f, -1.0f, -1.0f, -1.0f } },
        { { -1.0f, -1.0f, -1.0f, -1.0f },  { 2.0f, -1.0f, -1.0f, -1.0f },  { -1.0f, -1.0f, -1.0f, -1.0f } },
        { { -1.0f, 2.0f, -1.0f, -1.0f },  { -1.0f, 2.0f, -1.0f, -1.0f },  { -1.0f, 2.0f, -1.0f, -1.0f } }
    };
    //a V split
    inline const Filter3D layer3_turnV = {
        { { -1.0f, -1.0f, 2.0f, -1.0f },  { -1.0f, -1.0f, -1.0f, -1.0f },  { -1.0f, -1.0f, -1.0f, 2.0f } },
        { { -1.0f, -1.0f, -1.0f, -1.0f },  { -1.0f, -1.0f, 2.0f, 2.0f },  { -1.0f, -1.0f, -1.0f, -1.0f } },
        { { -1.0f, -1.0f, -1.0f, -1.0f },  { -1.0f, -1.0f, -1.0f, -1.0f },  { -1.0f, -1.0f, -1.0f, -1.0f } }
    };
    //a reverse V split
    inline const Filter3D layer3_turnVrev = {
        { { -1.0f, -1.0f, -1.0f, -1.0f },  { -1.0f, -1.0f, -1.0f, -1.0f },  { -1.0f, -1.0f, -1.0f, -1.0f } },
        { { -1.0f, -1.0f, -1.0f, -1.0f },  { -1.0f, -1.0f, 2.0f, 2.0f },  { -1.0f, -1.0f, -1.0f, -1.0f } },
        { { -1.0f, -1.0f, -1.0f, 2.0f },  { -1.0f, -1.0f, -1.0f, -1.0f },  { -1.0f, -1.0f, 2.0f, -1.0f } }
    };

    // --- 5. X-Cross Split (New Geometric Feature)
    // Reacts heavily when custom intersecting pathways meet across channels
    inline const Filter3D layer3_crossX = {
        { {  2.0f, -1.0f, -1.0f,  2.0f }, { -1.0f, -1.0f, -1.0f, -1.0f }, {  2.0f, -1.0f, -1.0f,  2.0f } },
        { { -1.0f, -1.0f, -1.0f, -1.0f }, { -1.0f,  2.0f,  2.0f, -1.0f }, { -1.0f, -1.0f, -1.0f, -1.0f } },
        { {  2.0f, -1.0f, -1.0f,  2.0f }, { -1.0f, -1.0f, -1.0f, -1.0f }, {  2.0f, -1.0f, -1.0f,  2.0f } }
    };

    // --- 6. Right-Facing Y/T Split (New Geometric Feature)
    inline const Filter3D layer3_turnRightT = {
        { {  2.0f,  2.0f, -1.0f, -1.0f }, { -1.0f, -1.0f, -1.0f, -1.0f }, { -1.0f, -1.0f, -1.0f, -1.0f } },
        { { -1.0f, -1.0f, -1.0f, -1.0f }, {  2.0f, -1.0f,  2.0f, -1.0f }, {  2.0f,  2.0f, -1.0f, -1.0f } },
        { {  2.0f,  2.0f, -1.0f, -1.0f }, { -1.0f, -1.0f, -1.0f, -1.0f }, { -1.0f, -1.0f, -1.0f, -1.0f } }
    };

    // --- 7. Channel Combiner Alpha (New Structural Combo)
    // Looks for simultaneous features: T-turn on Ch 0 AND V-split on Ch 2
    inline const Filter3D layer3_comboAlpha = {
        { {  2.0f, -1.0f,  2.0f, -1.0f }, {  2.0f, -1.0f, -1.0f, -1.0f }, {  2.0f, -1.0f, -1.0f,  2.0f } },
        { { -1.0f, -1.0f, -1.0f, -1.0f }, {  2.0f, -1.0f,  2.0f,  2.0f }, { -1.0f, -1.0f, -1.0f, -1.0f } },
        { { -1.0f, -1.0f, -1.0f, -1.0f }, {  2.0f, -1.0f, -1.0f, -1.0f }, { -1.0f, -1.0f, -1.0f, -1.0f } }
    };

    // --- 8. Channel Combiner Beta (New Structural Combo)
    // Looks for simultaneous features: Rev-T on Ch 1 AND Rev-V on Ch 3
    inline const Filter3D layer3_comboBeta = {
        { { -1.0f,  2.0f, -1.0f, -1.0f }, { -1.0f,  2.0f, -1.0f, -1.0f }, { -1.0f, -1.0f, -1.0f, -1.0f } },
        { { -1.0f, -1.0f, -1.0f, -1.0f }, { -1.0f,  2.0f,  2.0f,  2.0f }, { -1.0f, -1.0f, -1.0f, -1.0f } },
        { { -1.0f, -1.0f, -1.0f,  2.0f }, { -1.0f,  2.0f, -1.0f, -1.0f }, { -1.0f, -1.0f,  2.0f,  2.0f } }
    };
    
    inline std::vector<std::vector<std::vector<std::vector<float>>>> getLayer3Filters() {
        return { layer3_turnT, layer3_turnTrev, layer3_turnV, layer3_turnVrev,
                layer3_crossX, layer3_turnRightT, layer3_comboAlpha, layer3_comboBeta
            };
    }
    
    ////////////////////////////////////////////////8-16
    using Tensor4D = std::vector<std::vector<std::vector<std::vector<float>>>>;
    inline Tensor4D getLayer4Filters() {
    // 16 Output Filters, 3x3 Size, looking at 8 Input Channels
        Tensor4D filters(16, std::vector<std::vector<std::vector<float>>>(
            3, std::vector<std::vector<float>>(
                3, std::vector<float>(8, -1.0f) // Ambient noise baseline
            )
        ));

        // Automatically distribute baseline feature recognition
        for (int f = 0; f < 16; ++f) {
            int primaryChannel = f % 8;
            int secondaryChannel = (f + 7) % 8;

            for (int ky = 0; ky < 3; ++ky) {
                for (int kx = 0; kx < 3; ++kx) {
                    // Focus heavily on center structures
                    if (ky == 1 && kx == 1) {
                        filters[f][ky][kx][primaryChannel] = 3.0f;
                        filters[f][ky][kx][secondaryChannel] = 2.0f;
                    } 
                    // Check supporting edges
                    else if ((ky + kx) % 2 == 0) {
                        filters[f][ky][kx][primaryChannel] = 1.0f;
                    }
                }
            }
        }
        return filters;
    }

    //////////////////////////////////////////////////////// 16-32
    inline Tensor4D getLayer5Filters() {
    // 32 Output Filters, 3x3 Size, looking at 16 Input Channels
        Tensor4D filters(32, std::vector<std::vector<std::vector<float>>>(
            3, std::vector<std::vector<float>>(
                3, std::vector<float>(16, -1.0f) // Ambient noise baseline
            )
        ));
        // Automatically distribute baseline feature recognition
        for (int f = 0; f < 32; ++f) {
            // Let each filter choose two main incoming channels to focus on
            int primaryChannel = f % 16;
            int secondaryChannel = (f + 7) % 16;

            for (int ky = 0; ky < 3; ++ky) {
                for (int kx = 0; kx < 3; ++kx) {
                    // Focus heavily on center structures
                    if (ky == 1 && kx == 1) {
                        filters[f][ky][kx][primaryChannel] = 3.0f;
                        filters[f][ky][kx][secondaryChannel] = 2.0f;
                    } 
                    // Check supporting edges
                    else if ((ky + kx) % 2 == 0) {
                        filters[f][ky][kx][primaryChannel] = 1.0f;
                    }
                }
            }
        }
        return filters;
    }

    //32-64
    inline Tensor4D getLayer6Filters() {
        // 64 Output Filters, 3x3 Size, looking at 32 Input Channels
        Tensor4D filters(64, std::vector<std::vector<std::vector<float>>>(
            3, std::vector<std::vector<float>>(
                3, std::vector<float>(32, -1.0f) // Ambient noise baseline
            )
        ));

        for (int f = 0; f < 64; ++f) {
            int primaryChannel = f % 32;
            int secondaryChannel = (f + 31) % 32; // Alternating dynamic shift pattern

            for (int ky = 0; ky < 3; ++ky) {
                for (int kx = 0; kx < 3; ++kx) {
                    // Strong weight at the core
                    if (ky == 1 && kx == 1) {
                        filters[f][ky][kx][primaryChannel] = 3.0f;
                        filters[f][ky][kx][secondaryChannel] = 2.0f;
                    } 
                    // Grid boundary check support
                    else if ((ky + kx) % 2 == 0) {
                        filters[f][ky][kx][primaryChannel] = 1.0f;
                    }
                }
            }
        }
        return filters;
    }


    
}
