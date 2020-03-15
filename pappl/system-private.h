//
// Private system header file for the Printer Application Framework
//
// Copyright © 2019-2020 by Michael R Sweet.
// Copyright © 2010-2019 by Apple Inc.
//
// Licensed under Apache License v2.0.  See the file "LICENSE" for more
// information.
//

#ifndef _PAPPL_SYSTEM_PRIVATE_H_
#  define _PAPPL_SYSTEM_PRIVATE_H_

//
// Include necessary headers...
//

#  include "base-private.h"
#  include "system.h"
#  include <grp.h>
#  include <sys/poll.h>


//
// Constants...
//

#  define _PAPPL_MAX_LISTENERS	32	// Maximum number of listener sockets


//
// Types and structures...
//

typedef struct _pappl_resource_s	// Resource
{
  char			*path,			// Path
			*format,		// Content type (MIME media type)
			*filename,		// Filename
			*language;		// Language (for strings)
  const void		*data;			// Static data
  size_t		length;			// Length of file/data
  pappl_resource_cb_t	cb;			// Dynamic callback
  void			*cbdata;		// Callback data
} _pappl_resource_t;

struct _pappl_system_s			// System data
{
  pthread_rwlock_t	rwlock;			// Reader/writer lock
  time_t		start_time,		// Startup time
			clean_time,		// Next clean time
			save_time,		// Do we need to save the config?
			shutdown_time;		// Shutdown requested?
  char			*hostname;		// Hostname
  int			port;			// Port number, if any
  char			*directory;		// Spool directory
  char			*logfile;		// Log filename, if any
  int			logfd;			// Log file descriptor, if any
  pappl_loglevel_t	loglevel;		// Log level
  char			*subtypes;		// DNS-SD sub-types, if any
  char			*auth_service;		// PAM authorization service, if any
  char			*admin_group;		// PAM administrative group, if any
  gid_t			admin_gid;		// PAM administrative group ID
  char			*session_key;		// Session key
  int			num_listeners;		// Number of listener sockets
  struct pollfd		listeners[_PAPPL_MAX_LISTENERS];
						// Listener sockets
  cups_array_t		*resources;		// Array of resources
  int			next_client;		// Next client number
  cups_array_t		*printers;		// Array of printers
  int			default_printer_id,	// Default printer-id
			next_printer_id;	// Next printer-id
  pappl_driver_cb_t	driver_cb;		// Driver callback
  void			*driver_cbdata;		// Driver callback data
  pappl_ipp_op_cb_t	op_cb;			// IPP operation callback
  void			*op_cbdata;		// IPP operation callback data
  pappl_save_cb_t	save_cb;		// Save callback
  void			*save_cbdata;		// Save callback data
};


//
// Functions...
//

extern void		_papplSystemCleanJobs(pappl_system_t *system) _PAPPL_PRIVATE;
extern _pappl_resource_t *_papplSystemFindResource(pappl_system_t *system, const char *path) _PAPPL_PRIVATE;
extern char		*_papplSystemMakeUUID(pappl_system_t *system, const char *printer_name, int job_id, char *buffer, size_t bufsize) _PAPPL_PRIVATE;


#endif // !_PAPPL_SYSTEM_PRIVATE_H_
