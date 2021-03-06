/**
 * @file FileSystemObject.hpp
 * @brief This class provides class for File System
 */

#ifndef FILE_SYSTEM_OBJ_HPP__
#define FILE_SYSTEM_OBJ_HPP__

#include "fat/ff.h"
#include "fat/disk/diskio.h"



/**
 * File System Class
 *
 * @ingroup BoardIO
 */
class FileSystemObject
{
    public:
        /**
         * Returns the root path of this drive, such as "0:" or "1:"
         */
        const char* getDrivePath() const
        {
            return mVolStr;
        }

        /**
         * Initializes the disk and mounts the storage
         * @returns TRUE if the disk is ready to be used.
         * @note If disk is not formatted correctly, FILE IO may fail
         */
        bool mount() const
        {
            /**
             * Try to initialize disk first, and if it fails, return its status
             * The f_mount() always works since it doesn't initialize the disk
             */
            if(RES_OK != disk_initialize(mVolNum)) {
                return false;
            }

            return (FR_OK == f_mount(mVolNum, (FATFS*)&mFileSystem));
        }

        /**
         * Get the drive's total capacity and available space
         * @param pTotalDriveSpaceKB    Pointer where total drive space in kilobytes will be written
         * @param pAvailableSpaceKB     Pointer where drive's available space in kilobytes will be written
         * @note The parameters will be written to zero if an error occurs during this operation.
         */
        FRESULT getDriveInfo(unsigned int* pTotalDriveSpaceKB, unsigned int* pAvailableSpaceKB) const
        {
            // This object will just point back to our mFileSystem using the mVolStr
            FATFS* pFatFs;

            *pTotalDriveSpaceKB = 0;
            *pAvailableSpaceKB = 0;
            unsigned long int fre_clust = 0;
            FRESULT result;

            if (FR_OK == (result = f_getfree(mVolStr, &fre_clust, &pFatFs)))
            {
                /* Get total sectors and free sectors */
                unsigned int totalSectors = (pFatFs->n_fatent - 2) * pFatFs->csize;
                unsigned int freeSectors = fre_clust * pFatFs->csize;

                /* Print free space in unit of KB (assuming 512 bytes/sector) */
                *pAvailableSpaceKB  = freeSectors / 2;
                *pTotalDriveSpaceKB = totalSectors / 2;
            }

            return result;
        }

        /**
         * Formats the drive with default allocation size
         */
        FRESULT format() const
        {
            return f_mkfs(mVolNum, 0, 0);
        }

    private:
        /// Allow only the Storage class to create us
        friend class Storage;

        /// Private constructor to forbid this object creation
        FileSystemObject(DriveNumberType volumeNum) :
            mVolNum(volumeNum)
        {
            mVolStr[0] = volumeNum + '0';
            mVolStr[1] = ':';
            mVolStr[2] = '\0';
        }

        FATFS mFileSystem;              ///< The File System FatFS Structure that is mounted
        const DriveNumberType mVolNum;  ///< The drive number
        char mVolStr[3];                ///< The drive number as string
};

#endif /* FILE_SYSTEM_OBJ_HPP__ */
