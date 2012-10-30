/**
 * @file logger.hpp
 * @brief Provides Logger base classes
 * @ingroup Utilities
 *
 * Version: 06192012    Initial
 */
#ifndef LOGGER_HPP_
#define LOGGER_HPP_



/**
 * This is the Log Buffer Base class that provides a way of logging a single message and acts like
 * a circular buffer because when the logger memory is full, a call to handleCompletedBuffer() is
 * made so that that Parent class can handle the data that is going to be over-written.
 *
 * @ingroup Utilities
 */
class LoggerBase
{
    public:
        /// Flushes the buffer using handleCompletedBuffer() and zeroes out mBuffInfo to prepare for re-use
        void flush();

    protected:
        /**
         * Constructor
         * @param pBuff The buffer pointer to store the data until flush() is called
         * @param size  The size of the buffer pointer: pBuff
         */
        LoggerBase(char* pBuff, int size) :
            mpBuffPtr(pBuff), mBuffPtrSize(size),mBuffUsage(0)
        {
        }

        /// Virtual destructor of this abstract class
        virtual ~LoggerBase(){}

        /**
         * Logs a message in the buffer.
         * @note This is protected because the parent class should put semaphore around
         *          this method since this is not a thread-safe method.
         * @post If/While Buffer gets full, flush() is called
         */
        void log(const char* pMessage);

        /**
         * The object inheriting this class needs to provide its way of flushing
         * the buffer when buffer becomes full or when flush() is called
         */
        virtual void handleCompletedBuffer(char* pBuff, unsigned int size)=0;

    private:
        char* mpBuffPtr;                 ///< Memory pointer to store buffer until flush()
        const unsigned int mBuffPtrSize; ///< Size allocated for mpBuffPtr
        unsigned int mBuffUsage;         ///< Actual usage of the mBuffInfo.pBufferPtr
};




/**
 * This is a CSV (Comma-separated value) logger that logs data values separated by a commas.
 * The intent is to provide a CSV log that can be opened up in an Excel file to assess the
 * logged values.
 *
 * Some of the methods can be overridden to attain more functionality out of this class.
 * handleCompletedBuffer() is a required override to store or print out the completed buffer.
 *
 * @ingroup Utilities
 */
class CSVLogger : public LoggerBase
{
    public:
        /**
         * @{ Logger functions to log a warning or an error message
         * @param pMessage  The string or null terminated data to log
         * @param pFuncName Optional parameter: The function name calling this method
         * @param pFilename Optional parameter: The file name calling this method
         * @param lineNum   Optional parameter: The software code line number calling this method
         */
        void logError  (const char* pMessage, const char* pFilename=0, const char* pFuncName=0, int lineNum=0);
        void logWarning(const char* pMessage, const char* pFilename=0, const char* pFuncName=0, int lineNum=0);
        void logInfo   (const char* pMessage, const char* pFilename=0, const char* pFuncName=0, int lineNum=0);
        /** @} */

    protected:
        /**
         * Constructor
         * @param pBuff The buffer pointer to store the data until flush() is called
         * @param size  The size of the buffer pointer: pBuff
         */
        CSVLogger(char* pBuff, int size) : LoggerBase(pBuff, size) {}

        /// Virtual destructor of this abstract class
        virtual ~CSVLogger() {}

        /**
         * The object inheriting this class needs to provide its way of flushing
         * the buffer when buffer becomes full or when flush() is called
         */
        virtual void handleCompletedBuffer(char* pBuff, unsigned int size)=0;

        /**
         * @{ \name Semaphore Functions that parent class can override
         * If this class is used in multi-tasking environment, the logger functions
         * may not log data correctly without overriding these methods.
         */
        virtual void semTake(){}
        virtual void semGive(){}
        /** @} */

        /// Virtual method parent class can override to provide timestamps for logged messages
        virtual unsigned int getTimestamp() { return 0; }

    private:
        /**
         * Logs a message separated by commas that has 6 columns:
         *  Timestamp, pInfoType, Message, File name, Function Name, Line Number
         * @param pInfoType  The type of information being logged, such as "ERROR" or "INFO"
         * @param pMessage   The message to log, can be NULL pointer if no message
         * @param pFuncName  Optional parameter: The function name calling this method
         * @param pFilename  Optional parameter: The file name calling this method
         * @param lineNum    Optional parameter: The software code line number calling this method
         */
        void logCsvMessage(const char* pInfoType, const char* pMessage,
                           const char* pFilename=0, const char* pFuncName=0, int lineNum=0);
};

#endif /* LOGGER_HPP_ */
