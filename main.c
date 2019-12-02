#include "sdcard.h"

int main(void)
{
    /*The following is correct*/
    startSSI1();
    initialize_sd(SSI1);
    cs_high(SSI1);
    change_speed(SSI1);
    cs_low(SSI1);
    read_first_sector(SSI1);
    read_disk_data(SSI1);

    /*The cluster you get in the next line is the one of the root directory, even though the the only thing you have in the SD card is the file. In the acknowledgements section of the project's PDF you have some links where the filesystem is explained in case you want to learn more */
    long next_cluster=get_root_dir_first_cluster();

    /*Once you get the cluster of the root, directory, you need to execute the following in order to fill the structure with the data of the files. By the structure I mean what you can see defined on the top of the sdcard.c file with the name file_dir */
    do
    {
        next_cluster=list_dirs_and_files(next_cluster,SHORT_NAME,NO_SUBDIRS,SSI1);
    }while(next_cluster!=0x0FFFFFFF && next_cluster!=0xFFFFFFFF);

    //Here you can ask for the cluster of the file to be opened. In this example I try to get the cluster of file in position 5 in my structure:
    next_cluster=get_first_cluster(0); //Note, if you have only one file, it should be located in position 0


    do
    {
        next_cluster=open_file(next_cluster,SSI1);
    }while(next_cluster!=0x0FFFFFFF && next_cluster!=0xFFFFFFFF);

    return 0;
}

