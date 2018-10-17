// Helper functions for music

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

#include "helpers.h"

// Converts a fraction formatted as X/Y to eighths
int duration(string fraction)
{
    // get numerator and denominator of fraction and store them into variables
    // & returns the actual address of the variable
    int numerator = atoi(&fraction[0]); // => use & because fraction[] is a pointer! (&fraction points to adress)
    int denominator = atoi(&fraction[2]);
    int result = (numerator * 8) / denominator;

    return result;
}

// Calculates frequency (in Hz) of a note
int frequency(string note)
{
    char noteletter = note[0];
    int octave = 0;

    // Calculate frequency
    double frequency = 440.0;

    // Support all notes
    // from note A as starting point, find out how many semitones note is away
    // The frequency, f, of some note is 2 to the power of n/12 × 440, where n is the number of semitones from that note to A4
    if (noteletter == 'A')
    {
        frequency = 440.0;
    }
    else if (noteletter == 'G')
    {
        frequency = frequency / (pow(2.0, (2.0 / 12.0))); // => 2 hoch 2/12
    }
    else if (noteletter == 'F')
    {
        frequency = frequency / (pow(2.0, (4.0 / 12.0)));
    }
    else if (noteletter == 'E')
    {
        frequency = frequency / (pow(2.0, (5.0 / 12.0)));
    }
    else if (noteletter == 'D')
    {
        frequency = frequency / (pow(2.0, (7.0 / 12.0)));
    }
    else if (noteletter == 'C')
    {
        frequency = frequency / (pow(2.0, (9.0 / 12.0)));
    }
    else if (noteletter == 'B')
    {
        frequency = frequency * (pow(2.0, (2.0 / 12.0))); // => here * because B is the only note that is "above" A, here.
        // all the others are below A and therefore /
    }

    // get the info: octave or #/b?
    // if the second note is a sharp or flat indicator, remember this and use the third character as the octave
    // otherwise the second and final character is the octave.
    if (note[1] == 'b')
    {
        octave = atoi(&note[2]); // => use atoi because octave == int and note == char
        // => use & because note[] is a pointer
        frequency /= (pow(2.0, (1.0 / 12.0)));
    }
    else if (note[1] == '#')
    {
        octave = atoi(&note[2]);
        frequency *= (pow(2.0, (1.0 / 12.0)));
    }
    else
    {
        octave = atoi(&note[1]);
    }

    // Implement Octave of A - A4 = 440
    // if octave < 4 => 440/2,4,8,16 each octave *2
    if (octave < 4)
    {
        for (int i = 0; i < 4 - octave; i++)
        {
            frequency /= 2.0;
        }
    }
    // if octave > 4 => 440*2,4,8,16 each octave *2
    else if (octave > 4)
    {
        for (int i = 0; i < octave - 4; i++)
        {
            frequency *= 2.0;
        }
    }


    frequency = round(frequency);
    return frequency;
}

// Determines whether a string represents a rest
bool is_rest(string s)
{
    if (s[0] == '\0')
    {
        return true;
    }

    else
    {
        return false;
    }
}
