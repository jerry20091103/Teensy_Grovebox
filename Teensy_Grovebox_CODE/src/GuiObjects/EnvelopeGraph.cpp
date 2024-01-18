#include "EnvelopeGraph.h"
#include "Pages/GuiUtility.h"
#include "Colors.h"

void EnvelopeGraph::createGraph(lv_obj_t *parent, int16_t w, int16_t h, int16_t lineWidth, int16_t padding)
{
    graph = lv_obj_create(parent);
    lv_obj_remove_style_all(graph);
    lv_obj_set_size(graph, w, h);
    lv_obj_set_style_pad_all(graph, padding, 0);
    lv_obj_set_align(graph, LV_ALIGN_TOP_LEFT);

    static lv_style_t lineStyle;
    lv_style_init(&lineStyle);
    lv_style_set_line_width(&lineStyle, lineWidth);
    lv_style_set_line_rounded(&lineStyle, true);

    delayLine = lv_line_create(graph);
    lv_obj_set_style_line_color(delayLine, lv_color_white(), 0);
    lv_obj_add_style(delayLine, &lineStyle, 0);
    lv_line_set_y_invert(delayLine, true);

    attackLine = lv_line_create(graph);
    lv_obj_set_style_line_color(attackLine, color_Red, 0);
    lv_obj_add_style(attackLine, &lineStyle, 0);
    lv_line_set_y_invert(attackLine, true);

    decayLine = lv_line_create(graph);
    lv_obj_set_style_line_color(decayLine, color_Yellow, 0);
    lv_obj_add_style(decayLine, &lineStyle, 0);
    lv_line_set_y_invert(decayLine, true);

    sustainLine = lv_line_create(graph);
    lv_obj_set_style_line_color(sustainLine, color_Blue, 0);
    lv_obj_add_style(sustainLine, &lineStyle, 0);
    lv_line_set_y_invert(sustainLine, true);

    releaseLine = lv_line_create(graph);
    lv_obj_set_style_line_color(releaseLine, color_Green, 0);
    lv_obj_add_style(releaseLine, &lineStyle, 0);
    lv_line_set_y_invert(releaseLine, true);
}

EnvelopeGraph::EnvelopeGraph(lv_obj_t *parent, int16_t w, int16_t h, int16_t lineWidth, int16_t padding)
{
    this->lineWidth = lineWidth;
    this->padding = padding;
    createGraph(parent, w, h, lineWidth, padding);
}

EnvelopeGraph::~EnvelopeGraph()
{
    lv_obj_del(graph);
}

void EnvelopeGraph::setEnvelope(float delay, float attack, float decay, float sustain, float release)
{
    // get graph width and height (minus the padding)
    int16_t graphWidth = lv_obj_get_width(graph) - padding - lineWidth/2;
    int16_t graphHeight = lv_obj_get_height(graph)  - padding - lineWidth/2;
    // get total time length in ms
    float total = delay + attack + decay + release;
    // add padding if total length is less then 200ms (value debatable)
    if (total < 200)
        total = 200;
    // get absolute length in the graph
    // we want sustain to occupy a certain percentage of the graph width regardless of total time length
    int16_t sustain_abs = graphWidth / 5 - total / 40000 * graphWidth / 10; // sustain_abs is between 1/5 and 1/10 of the graph width, it gets smaller as total gets bigger
    int16_t widthRemain = graphWidth - sustain_abs;
    int16_t delay_abs = delay / total * widthRemain;
    int16_t attack_abs = attack / total * widthRemain;
    int16_t decay_abs = decay / total * widthRemain;
    int16_t release_abs = release / total * widthRemain;
    // set the lvgl points
    // each points gets two points, in the order of delay, attack, decay, sustain, release
    // the coordinate is relative to the line object itself
    points[0] = {0, 0};
    points[1] = {delay_abs, 0};
    points[2] = {0, 0};
    points[3] = {attack_abs, graphHeight};
    points[4] = {0, graphHeight};
    points[5] = {decay_abs, (int16_t)(sustain * graphHeight)};
    points[6] = {0, (int16_t)(sustain * graphHeight)};
    points[7] = {sustain_abs, (int16_t)(sustain * graphHeight)};
    points[8] = {0, (int16_t)(sustain * graphHeight)};
    points[9] = {release_abs, 0};
    // delay line
    lv_obj_set_size(delayLine, delay_abs, graphHeight);
    lv_line_set_points(delayLine, &points[0], 2);
    // attack line
    lv_obj_set_size(attackLine, attack_abs, graphHeight);
    lv_line_set_points(attackLine, &points[2], 2);
    lv_obj_set_x(attackLine, delay_abs);
    // decay line
    lv_obj_set_size(decayLine, decay_abs, graphHeight);
    lv_line_set_points(decayLine, &points[4], 2);
    lv_obj_set_x(decayLine, delay_abs + attack_abs);
    // sustain line
    lv_obj_set_size(sustainLine, sustain_abs, graphHeight);
    lv_line_set_points(sustainLine, &points[6], 2);
    lv_obj_set_x(sustainLine, delay_abs + attack_abs + decay_abs);
    // release line
    lv_obj_set_size(releaseLine, release_abs, graphHeight);
    lv_line_set_points(releaseLine, &points[8], 2);
    lv_obj_set_x(releaseLine, delay_abs + attack_abs + decay_abs + sustain_abs);
}
