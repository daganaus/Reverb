#pragma once

#include <algorithm> // pour std::fill si besoin

class Edge  // A circular buffer for storing audio samples
{
public:
    Edge(int length);

    ~Edge() ;

    // Ajoute un sample dans le buffer circulaire
    void pushSample(float sample);

    // Récupère le sample à une position relative (0 = plus récent)
    float getSample(int offset = 0) const;

    int getLength() const;
    float* getBuffer() const;
    int getHead() const;

private:
    int length; // longueur du buffer circulaire
    float* buffer;
    int head; // position d'écriture courante
};