#include "Snake.h"

Snake::Snake(int start_x, int start_y, int size) {
    segments.push_back({start_x, start_y});
}

const std::vector<SnakeSegment>& Snake::getSegments() const {
    return segments;
}

std::vector<SnakeSegment>& Snake::getSegments() {
    return segments;
}
