/*
  main.c: final exam | sample audio from the microphone and write to a .wav file
  
  Copyright (c) 2019 Gustavo Santana, Lúcio Franco

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

    You can also obtain a copy of the GNU General Public License
    at <http://www.gnu.org/licenses>.

*/

#include <byteswap.h>
#include <fcntl.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <galileo2io.h>
#include "adc.h"

#define device_path "/dev/iio:device0"
#define scale_path "/sys/bus/iio/devices/iio:device0/in_voltage0_scale"

// WAVE file header format
// adapted from the pcm-to-wav lib
typedef struct {
    unsigned char   chunk_id[4];        // RIFF string
    unsigned int    chunk_size;         // overall size of file in bytes (36 + data_size)
    unsigned char   sub_chunk1_id[8];   // WAVEfmt string with trailing null char
    unsigned int    sub_chunk1_size;    // 16 for PCM.  This is the size of the rest of the Subchunk which follows this number.
    unsigned short  audio_format;       // format type. 1-PCM, 3- IEEE float, 6 - 8bit A law, 7 - 8bit mu law
    unsigned short  num_channels;       // Mono = 1, Stereo = 2
    unsigned int    sample_rate;        // 8000, 16000, 44100, etc. (blocks per second)
    unsigned int    byte_rate;          // SampleRate * NumChannels * BitsPerSample/8
    unsigned short  block_align;        // NumChannels * BitsPerSample/8
    unsigned short  bits_per_sample;    // bits per sample, 8- 8bits, 16- 16 bits etc
    unsigned char   sub_chunk2_id[4];   // Contains the letters "data"
    unsigned int    sub_chunk2_size;    // NumSamples * NumChannels * BitsPerSample/8 - size of the next chunk that will be read
} wav_header_t;


char* dummy_get_raw_pcm(char *p, int *bytes_read)
{
    long lSize;
    char *pcm_buf;
    size_t result;
    FILE *fp_pcm;

    fp_pcm = fopen (p, "rb");
    if (fp_pcm == NULL) {
        printf ("File error");
        exit (1);
    }

    // obtain file size:
    fseek (fp_pcm , 0 , SEEK_END);
    lSize = ftell (fp_pcm);
    rewind (fp_pcm);

    // allocate memory to contain the whole file:
    pcm_buf = (char*) malloc (sizeof(char) * lSize);
    if (pcm_buf == NULL) {
        printf ("Memory error");
        exit (2);
    }

    // copy the file into the pcm_buf:
    result = fread(pcm_buf, 1, lSize, fp_pcm);
    if (result != lSize) {
        printf ("Reading error");
        exit (3);
    }

    *bytes_read = (int) lSize;
    return pcm_buf;
}

void get_wav_header(int raw_sz, wav_header_t *wh)
{
    // RIFF chunk
    wh->chunk_id[0] = "R";
    wh->chunk_id[1] = "I";
    wh->chunk_id[2] = "F";
    wh->chunk_id[3] = "F";
    wh->chunk_size = 36 + raw_sz;

    // fmt sub-chunk (to be optimized)
    wh->sub_chunk1_id[0] = "W";
    wh->sub_chunk1_id[1] = "A";
    wh->sub_chunk1_id[2] = "V";
    wh->sub_chunk1_id[3] = "E";
    wh->sub_chunk1_id[4] = "f";
    wh->sub_chunk1_id[5] = "m";
    wh->sub_chunk1_id[6] = "t";
    wh->sub_chunk1_id[7] = " ";
    wh->sub_chunk1_size = 16;
    wh->audio_format = 1;
    wh->num_channels = 1;
    wh->sample_rate = 4000; // 4kHz
    wh->bits_per_sample = 16; // PCM ~ 16bits
    wh->block_align = wh->num_channels * wh->bits_per_sample / 8;
    wh->byte_rate = wh->sample_rate * wh->num_channels * wh->bits_per_sample / 8;

    // data sub-chunk
    wh->sub_chunk2_id[0] = "d";
    wh->sub_chunk2_id[1] = "a";
    wh->sub_chunk2_id[2] = "t";
    wh->sub_chunk2_id[3] = "a";
    wh->sub_chunk2_size = 4000 * 1 * 16 / 8; //NumSamples * NumChannels * BitsPerSample/8;
}

int main(int argc, char const *argv[])
{
    // *****************
    // ADC SECTION
    // *****************
    ADC adc;

    if(argc != 2)
    {
        puts("usage: main <file_path>");
        return -1;
    }

    // initialize ADC
    // adc_open(&adc, device_path, scale_path);

    // read samples with 4kHz
    // 16k samples = 4 seconds
    // sample_size   = 16000;
    // sampling_rate = 0.00025; // 0.25ms = 4kHz
    adc_continuous_read_begin(); // writes to data.pcm

    // *****************
    // PCM/WAV SECTION
    // *****************
    // int raw_sz = 2048;
    // FILE *fwav;
    // wav_header_t wheader;

    // memset (&wheader, '\0', sizeof (wav_header_t));

    // // check argument
    // if (argc != 2)
    //     return -1;

    // // dummy raw pcm data
    // char *pcm_buf = dummy_get_raw_pcm("./data.pcm", &raw_sz); // reads from data.pcm

    // // construct wav header
    // get_wav_header (raw_sz, &wheader);

    // // write out the .wav file
    // fwav = fopen(argv[1], "wb");
    // fwrite(&wheader, 1, sizeof(wheader), fwav);
    // fwrite(pcm_buf, 1, raw_sz, fwav);
    // fclose(fwav);

    // if (pcm_buf)
    //     free (pcm_buf);

    return 0;
}