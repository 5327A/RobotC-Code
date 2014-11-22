#include <FlashLib.h>

task main()
{
    int   i;
    unsigned char *data;
    int           datalength;

    // dump directory
    RCFS_ReadVTOC();

    // Get a pointer to the data in that last file
    // Pass the address of the data pointer (we call that a handle)
    if( RCFS_GetFile( "rerunData.txt", &data, &datalength ) == RCFS_SUCCESS )
    {
    for(i=0;i<14992;i++)
        writeDebugStream("%f ", *(data) );
    writeDebugStreamLine("");
    }
}
