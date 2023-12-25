#pragma once

#include <vector>

struct SnakeSegment {
    int x, y;
};

class Snake {
public:
    Snake(int start_x, int start_y, int size);

    const std::vector<SnakeSegment>& getSegments() const;
    std::vector<SnakeSegment>& getSegments();

private:
    std::vector<SnakeSegment> segments;
};
