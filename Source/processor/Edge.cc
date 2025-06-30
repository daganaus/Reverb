//Member functions for Edge class
// A circular buffer for storing audio samples
#include "Edge.h"
#include <algorithm> // pour std::fill si besoin

Edge::Edge(int len)
        : length(len), buffer(new float[len]), head(0)
    {
        std::fill(buffer, buffer + len, 0.0f);
    }

Edge::~Edge()
{
	delete[] buffer;
	buffer = nullptr;
}

void Edge::pushSample(float sample)
{
	head = (head - 1 + length) % length;
	buffer[head] = sample;
}

float Edge::getSample(int offset) const
{
	int idx = (head - 1 - offset + length) % length;
	return buffer[idx];
}

int Edge::getLength() const
{
	return length;
}

float* Edge::getBuffer() const
{
	return buffer;
}

int Edge::getHead() const
{
	return head;
}