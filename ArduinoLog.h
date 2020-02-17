/*
    _   ___ ___  _   _ ___ _  _  ___  _    ___   ___
   /_\ | _ \   \| | | |_ _| \| |/ _ \| |  / _ \ / __|
  / _ \|   / |) | |_| || || .` | (_) | |_| (_) | (_ |
 /_/ \_\_|_\___/ \___/|___|_|\_|\___/|____\___/ \___|

  Log library for Arduino
  version 1.0.3
  https://github.com/thijse/Arduino-Log

Licensed under the MIT License <http://opensource.org/licenses/MIT>.

*/

#ifndef LOGGING_H
#define LOGGING_H
#include <inttypes.h>
#include <stdarg.h>

#if defined(ARDUINO) && ARDUINO >= 100
	#include "Arduino.h"
#else
	#include "WProgram.h"
#endif
typedef void (*printfunction)(Print*);

//#include <stdint.h>
//#include <stddef.h>
// *************************************************************************
//  Uncomment line below to fully disable logging, and reduce project size
// ************************************************************************
//#define DISABLE_LOGGING

#define LOG_LEVEL_SILENT  0
#define LOG_LEVEL_FATAL   1
#define LOG_LEVEL_ERROR   2
#define LOG_LEVEL_WARN    3
#define LOG_LEVEL_INFO    4
#define LOG_LEVEL_DEBUG   5
#define LOG_LEVEL_TRACE   6

#define CR "\n"
#define LOGGING_VERSION 2_0_0

/**
 * Logging is a helper class to output informations over
 * RS232. If you know log4j or log4net, this logging class
 * is more or less similar ;-) <br>
 * Different loglevels can be used to extend or reduce output
 * All methods are able to handle any number of output parameters.
 * All methods print out a formated string (like printf).<br>
 * To reduce output and program size, reduce loglevel.
 *
 * Version 2 uses the Print target's implementation of printf.
 *
 * ---- Loglevels
 * 
 * 0 - LOG_LEVEL_SILENT     no output
 * 1 - LOG_LEVEL_FATAL      fatal errors
 * 2 - LOG_LEVEL_ERROR      all errors
 * 3 - LOG_LEVEL_WARN       errors and warnings
 * 4 - LOG_LEVEL_INFO       errors, warnings and notices
 * 5 - LOG_LEVEL_DEBUG      errors, warnings, notices, traces
 * 6 - LOG_LEVEL_TRACE      all
 */

class Logging
{
public:
	/**
	 * default Constructor
	 */
	Logging()
#ifndef DISABLE_LOGGING
		: _level(LOG_LEVEL_SILENT),
		_showLevel(true),
		_logOutput(nullptr)
#endif
	{

	}

	/**
	 * Initializing, must be called as first. Note that if you use
	 * this variant of Init, you need to initialize the baud rate
	 * yourself, if printer happens to be a serial port.
	 * 
	 * \param level - logging levels <= this will be logged.
	 * \param printer - place that logging output will be sent to.
	 * \return void
	 *
	 */
	void begin(int level, Print *output, bool showLevel = true);

	/**
	 * Set the log level.
	 * 
	 * \param level - The new log level.
	 * \return void
	 */
	void setLevel(int level);

	/**
	 * Get the log level.
	 *
	 * \return The current log level.
	 */
	int getLevel() const;

	/**
	 * Set whether to show the log level.
	 * 
	 * \param showLevel - true if the log level should be shown for each log
	 *                    false otherwise.
	 * \return void
	 */
	void setShowLevel(bool showLevel);

	/**
	 * Get whether the log level is shown during logging
	 * 
	 * \return true if the log level is be shown for each log
	 *         false otherwise.
	 */
	bool getShowLevel() const;

	/**
	 * Sets a function to be called before each log command.
	 * 
	 * \param f - The function to be called
	 * \return void
	 */
	void setPrefix(printfunction f);

	/**
	 * Sets a function to be called after each log command.
	 * 
	 * \param f - The function to be called
	 * \return void
	 */
	void setSuffix(printfunction f);

	/**
	 * Output a fatal error message. Output message contains
	 * F: followed by original message
	 * Fatal error messages are printed out at
	 * loglevels >= LOG_LEVEL_FATAL
	 * 
	 * \param msg format string to output
	 * \param ... any number of variables
	 * \return void
	 */
	template <class T, typename... Args> void fatal(T msg, Args... args)
	{
#ifndef DISABLE_LOGGING
		printLevel(LOG_LEVEL_FATAL, msg, args...);
#endif
	}

	/**
	 * Output an error message. Output message contains
	 * E: followed by original message
	 * Error messages are printed out at
	 * loglevels >= LOG_LEVEL_ERROR
	 * 
	 * \param msg format string to output
	 * \param ... any number of variables
	 * \return void
	 */
	template <class T, typename... Args> void error(T msg, Args... args){
#ifndef DISABLE_LOGGING
		printLevel(LOG_LEVEL_ERROR, msg, args...);
#endif
	}

	/**
	 * Output a warning message. Output message contains
	 * W: followed by original message
	 * Warning messages are printed out at
	 * loglevels >= LOG_LEVEL_WARN
	 * 
	 * \param msg format string to output
	 * \param ... any number of variables
	 * \return void
	 */
	template <class T, typename... Args> void warn(T msg, Args...args)
	{
#ifndef DISABLE_LOGGING
		printLevel(LOG_LEVEL_WARN, msg, args...);
#endif
	}

	/**
	 * Output a info message. Output message contains
	 * N: followed by original message
	 * Notice messages are printed out at
	 * loglevels >= LOG_LEVEL_INFO
	 * 
	 * \param msg format string to output
	 * \param ... any number of variables
	 * \return void
	 */
	template <class T, typename... Args> void info(T msg, Args...args)
	{
#ifndef DISABLE_LOGGING
		printLevel(LOG_LEVEL_INFO, msg, args...);
#endif
	}

	/**
	 * Output a debug message. Output message contains
	 * N: followed by original message
	 * Trace messages are printed out at
	 * loglevels >= LOG_LEVEL_DEBUG
	 * 
	 * \param msg format string to output
	 * \param ... any number of variables
	 * \return void
	*/
	template <class T, typename... Args> void debug(T msg, Args... args)
	{
#ifndef DISABLE_LOGGING
		printLevel(LOG_LEVEL_DEBUG, msg, args...);
#endif
	}

	/**
	 * Output a trace message. Output message contains
	 * V: followed by original message
	 * Debug messages are printed out at
	 * loglevels >= LOG_LEVEL_TRACE
	 * 
	 * \param msg format string to output
	 * \param ... any number of variables
	 * \return void
	 */
	template <class T, typename... Args> void trace(T msg, Args... args)
	{
#ifndef DISABLE_LOGGING
		printLevel(LOG_LEVEL_TRACE  , msg, args...);
#endif
	}

private:
	template <class T, class... Args> void printLevel(int level, T msg, Args... args)
	{
#ifndef DISABLE_LOGGING
		if (level > _level)
		{
			return;
		}

		if (_prefix != nullptr)
		{
			_prefix(_logOutput);
		}

		if (_showLevel) {
			static const char levels[] = "FEWIDT";
			_logOutput->print(levels[level - 1]);
			_logOutput->print(": ");
		}

		_logOutput->printf(msg, args...);

		if(_suffix != nullptr)
		{
			_suffix(_logOutput);
		}
#endif
	}

#ifndef DISABLE_LOGGING
	int _level;
	bool _showLevel;
	Print* _logOutput;

	printfunction _prefix = nullptr;
	printfunction _suffix = nullptr;
#endif
};

extern Logging Log;
#endif

