#ifndef ENVELOPE_GRAPH_H
#define ENVELOPE_GRAPH_H

#include "lvgl.h"
/* EnvelopeGraph GUI object
Displays the DADSR envelope graph.
*/

class EnvelopeGraph
{
private:
    // lvgl objects
    lv_obj_t *graph = NULL;
    lv_obj_t *delayLine = NULL;
    lv_obj_t *attackLine = NULL;
    lv_obj_t *decayLine = NULL;
    lv_obj_t *sustainLine = NULL;
    lv_obj_t *releaseLine = NULL;
    // lvgl points for the lvgl lines
    lv_point_t points[10];
    // other private methods
    void createGraph(lv_obj_t *parent, int16_t w, int16_t h, int16_t lineWidth, int16_t padding);
    // other variables
    int16_t lineWidth = 8;
    int16_t padding = 5;
public:
    EnvelopeGraph(lv_obj_t *parent, int16_t w, int16_t h, int16_t lineWidth = 8, int16_t padding = 5);
    ~EnvelopeGraph();
    void setEnvelope(float delay, float attack, float decay, float sustain, float release);
    lv_obj_t* getLvglObject() { return graph; }
};

#endif // ENVELOPE_GRAPH_H