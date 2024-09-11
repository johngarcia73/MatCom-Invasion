#include"audio.h"
#include"control.h"

#define BITS 8
bool play = true;

void initAudio()
{
    createThread(playAudio);
}
void* playAudio(void* thr)
{
    while(1)
    {
        char *filename = "audio/GameMusic.mp3";
        ao_initialize();
        int driver = ao_default_driver_id();
        mpg123_init();
        mpg123_handle *mh = mpg123_new(NULL, NULL);
        unsigned char *buffer;
        size_t buffer_size;
        size_t done;
        int err;
        
        long rate;
        int channels, encoding;

        mpg123_open(mh, filename);
        mpg123_getformat(mh, &rate, &channels, &encoding);

        ao_sample_format format;
        format.bits = mpg123_encsize(encoding) * BITS;
        format.rate = rate;
        format.channels = channels;
        format.byte_format = AO_FMT_NATIVE;
        format.matrix  = 0;

        ao_device *device = ao_open_live(driver, &format, NULL);

        buffer_size = mpg123_outblock(mh);
        buffer = (unsigned char *)malloc(buffer_size * sizeof(unsigned char *));

        while (mpg123_read(mh, buffer, buffer_size, &done) == MPG123_OK)
        {
            ao_play(device, (char *)buffer, done);
        }

        free(buffer);
        ao_close(device);
        mpg123_close(mh);
        mpg123_delete(mh);
        mpg123_exit();
        ao_shutdown();
    }
    pthread_exit(NULL);
}