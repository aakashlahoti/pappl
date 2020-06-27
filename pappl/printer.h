//
// Printer header file for the Printer Application Framework
//
// Copyright © 2019-2020 by Michael R Sweet.
//
// Licensed under Apache License v2.0.  See the file "LICENSE" for more
// information.
//

#ifndef _PAPPL_PRINTER_H_
#  define _PAPPL_PRINTER_H_


//
// Include necessary headers...
//

#  include "base.h"


//
// C++ magic...
//

#  ifdef __cplusplus
extern "C" {
#  endif // __cplusplus


//
// Limits...
//

#  define PAPPL_MAX_BIN		16	// Maximum number of output bins
#  define PAPPL_MAX_COLOR_MODE	8	// Maximum number of color modes
#  define PAPPL_MAX_MEDIA	256	// Maximum number of media sizes
#  define PAPPL_MAX_RASTER_TYPE	16	// Maximum number of raster types
#  define PAPPL_MAX_RESOLUTION	4	// Maximum number of printer resolutions
#  define PAPPL_MAX_SOURCE	16	// Maximum number of sources/rolls
#  define PAPPL_MAX_SUPPLY	32	// Maximum number of supplies
#  define PAPPL_MAX_TYPE	32	// Maximum number of media types
#  define PAPPL_MAX_VENDOR	32	// Maximum number of vendor extension attributes


//
// Constants...
//

enum pappl_color_mode_e			// IPP "print-color-mode" bit values
{
  PAPPL_COLOR_MODE_AUTO = 0x0001,		// 'auto' - Automatic color/monochrome print mode
  PAPPL_COLOR_MODE_AUTO_MONOCHROME = 0x0002,	// 'auto-monochrome' - Automatic monochrome/process monochrome print mode
  PAPPL_COLOR_MODE_BI_LEVEL = 0x0004,		// 'bi-level' - B&W (threshold) print mode
  PAPPL_COLOR_MODE_COLOR = 0x0008,		// 'color' - Full color print mode
  PAPPL_COLOR_MODE_MONOCHROME = 0x0010,		// 'monochrome' - Grayscale print mode using 1 color
  PAPPL_COLOR_MODE_PROCESS_MONOCHROME = 0x0020	// 'process-monochrome' - Grayscale print mode using multiple colors
};
typedef unsigned pappl_color_mode_t;	// Bitfield for IPP "print-color-mode" values

enum pappl_content_e			// IPP "print-content-optimize" bit values
{
  PAPPL_CONTENT_AUTO = 0x01,			// 'auto': Automatically determine content
  PAPPL_CONTENT_GRAPHIC = 0x02,			// 'graphic': Optimize for vector graphics
  PAPPL_CONTENT_PHOTO = 0x04,			// 'photo': Optimize for photos/continuous tone images
  PAPPL_CONTENT_TEXT = 0x08,			// 'text': Optimize for text
  PAPPL_CONTENT_TEXT_AND_GRAPHIC = 0x10		// 'text-and-graphic': Optimize for text and vector graphics
};
typedef unsigned pappl_content_t;	// Bitfield for IPP "print-content-optimize" values

typedef enum pappl_duplex_e		// Duplex printing support
{
  PAPPL_DUPLEX_NONE,				// No duplex printing support
  PAPPL_DUPLEX_NORMAL,				// Duplex with normal back sides
  PAPPL_DUPLEX_FLIPPED,				// Duplex with flipped back sides
  PAPPL_DUPLEX_ROTATED,				// Duplex with back side rotated 180 degrees for long-edge duplex
  PAPPL_DUPLEX_MANUAL_TUMBLE			// Duplex with back side rotated 180 degrees for short-edge duplex
} pappl_duplex_t;

enum pappl_finishings_e			// IPP "finishings" bit values
{
  PAPPL_FINISHINGS_NONE = 0x0000,		// 'none'
  PAPPL_FINISHINGS_PUNCH = 0x0001,		// 'punch'
  PAPPL_FINISHINGS_STAPLE = 0x0002,		// 'staple'
  PAPPL_FINISHINGS_TRIM = 0x0004		// 'trim'
  // TODO: Determine if there are other common finishers appropriate to support
  // in PAPPL.  The full list is very long...
};
typedef unsigned pappl_finishings_t;	// Bitfield for IPP "finishings" values

enum pappl_identify_actions_e		// IPP "identify-actions" bit values
{
  PAPPL_IDENTIFY_ACTIONS_NONE = 0x0000,		// No actions
  PAPPL_IDENTIFY_ACTIONS_DISPLAY = 0x0001,	// 'display': Display a message
  PAPPL_IDENTIFY_ACTIONS_FLASH = 0x0002,	// 'flash': Flash the display or a light
  PAPPL_IDENTIFY_ACTIONS_SOUND = 0x0004,	// 'sound': Make a sound
  PAPPL_IDENTIFY_ACTIONS_SPEAK = 0x0008		// 'speak': Speak a message
};
typedef unsigned pappl_identify_actions_t;
					// Bitfield for IPP "identify-actions" values

enum pappl_kind_e			// IPP "printer-kind" bit values
{
  PAPPL_KIND_DISC = 0x0001,			// 'disc'
  PAPPL_KIND_DOCUMENT = 0x0002,			// 'document'
  PAPPL_KIND_ENVELOPE = 0x0004,			// 'envelope'
  PAPPL_KIND_LABEL = 0x0008,			// 'label'
  PAPPL_KIND_LARGE_FORMAT = 0x0010,		// 'large-format'
  PAPPL_KIND_PHOTO = 0x0020,			// 'photo'
  PAPPL_KIND_POSTCARD = 0x0040,			// 'postcard'
  PAPPL_KIND_RECEIPT = 0x0080,			// 'receipt'
  PAPPL_KIND_ROLL = 0x0100			// 'roll'
};
typedef unsigned pappl_kind_t;		// Bitfield for IPP "printer-kind" values

enum pappl_label_mode_e			// IPP "label-mode-xxx" bit values
{
  PAPPL_LABEL_MODE_APPLICATOR = 0x0001,		// 'applicator'
  PAPPL_LABEL_MODE_CUTTER = 0x0002,		// 'cutter'
  PAPPL_LABEL_MODE_CUTTER_DELAYED = 0x0004,	// 'cutter-delayed'
  PAPPL_LABEL_MODE_KIOSK = 0x0008,		// 'kiosk'
  PAPPL_LABEL_MODE_PEEL_OFF = 0x0010,		// 'peel-off'
  PAPPL_LABEL_MODE_PEEL_OFF_PREPEEL = 0x0020,	// 'peel-off-prepeel'
  PAPPL_LABEL_MODE_REWIND = 0x0040,		// 'rewind'
  PAPPL_LABEL_MODE_RFID = 0x0080,		// 'rfid'
  PAPPL_LABEL_MODE_TEAR_OFF = 0x0100		// 'tear-off'
};
typedef unsigned short pappl_label_mode_t;
					// Bitfield for IPP "label-mode-xxx" values

enum pappl_media_tracking_e		// IPP "media-tracking" bit values
{
  PAPPL_MEDIA_TRACKING_CONTINUOUS = 0x0001,	// 'continuous'
  PAPPL_MEDIA_TRACKING_GAP = 0x0002,		// 'gap'
  PAPPL_MEDIA_TRACKING_MARK = 0x0004,		// 'mark'
  PAPPL_MEDIA_TRACKING_WEB = 0x0008		// 'web'
};
typedef unsigned short pappl_media_tracking_t;
					// Bitfield for IPP "media-tracking" values

enum pappl_preason_e			// IPP "printer-state-reasons" bit values
{
  PAPPL_PREASON_NONE = 0x0000,			// 'none'
  PAPPL_PREASON_OTHER = 0x0001,			// 'other'
  PAPPL_PREASON_COVER_OPEN = 0x0002,		// 'cover-open'
  PAPPL_PREASON_INPUT_TRAY_MISSING = 0x0004,	// 'input-tray-missing'
  PAPPL_PREASON_MARKER_SUPPLY_EMPTY = 0x0008,	// 'marker-supply-empty'
  PAPPL_PREASON_MARKER_SUPPLY_LOW = 0x0010,	// 'marker-supply-low'
  PAPPL_PREASON_MARKER_WASTE_ALMOST_FULL = 0x0020,
						// 'marker-waste-almost-full'
  PAPPL_PREASON_MARKER_WASTE_FULL = 0x0040,	// 'marker-waste-full'
  PAPPL_PREASON_MEDIA_EMPTY = 0x0080,		// 'media-empty'
  PAPPL_PREASON_MEDIA_JAM = 0x0100,		// 'media-jam'
  PAPPL_PREASON_MEDIA_LOW = 0x0200,		// 'media-low'
  PAPPL_PREASON_MEDIA_NEEDED = 0x0400,		// 'media-needed'
  PAPPL_PREASON_SPOOL_AREA_FULL = 0x0800,	// 'spool-area-full'
  PAPPL_PREASON_TONER_EMPTY = 0x1000,		// 'toner-empty'
  PAPPL_PREASON_TONER_LOW = 0x2000,		// 'toner-low'

  PAPPL_PREASON_DEVICE_STATUS = 0x37ff		// Supported @link papplDeviceGetStatus@ bits
};

enum pappl_raster_type_e		// IPP "pwg-raster-document-type-supported" bit values
{
  PAPPL_PWG_RASTER_TYPE_NONE = 0x0000,		// Do not force a particular raster type
  PAPPL_PWG_RASTER_TYPE_ADOBE_RGB_8 = 0x0001,	// 8-bit per component AdobeRGB
  PAPPL_PWG_RASTER_TYPE_ADOBE_RGB_16 = 0x0002,	// 16-bit per component AdobeRGB
  PAPPL_PWG_RASTER_TYPE_BLACK_1 = 0x0004,	// 1-bit (device) black
  PAPPL_PWG_RASTER_TYPE_BLACK_8 = 0x0008,	// 8-bit (device) black
  PAPPL_PWG_RASTER_TYPE_BLACK_16 = 0x0010,	// 16-bit (device) black
  PAPPL_PWG_RASTER_TYPE_CMYK_8 = 0x0020,	// 8-bit per component (device) CMYK
  PAPPL_PWG_RASTER_TYPE_CMYK_16 = 0x0040,	// 16-bit per component (device) CMYK
  PAPPL_PWG_RASTER_TYPE_RGB_8 = 0x0080,		// 8-bit per component (device) RGB
  PAPPL_PWG_RASTER_TYPE_RGB_16 = 0x0100,	// 16-bit per component (device) RGB)
  PAPPL_PWG_RASTER_TYPE_SGRAY_8 = 0x0200,	// 8-bit grayscale with 2.2 gamma
  PAPPL_PWG_RASTER_TYPE_SGRAY_16 = 0x0400,	// 16-bit grayscale with 2.2 gamma
  PAPPL_PWG_RASTER_TYPE_SRGB_8 = 0x0800,	// 8-bit per component sRGB
  PAPPL_PWG_RASTER_TYPE_SRGB_16 = 0x1000	// 16-bit per component sRGB
};
typedef unsigned pappl_raster_type_t;	// Bitfield for IPP "pwg-raster-document-type-supported" values

enum pappl_scaling_e			// IPP "print-scaling" bit values
{
  PAPPL_SCALING_AUTO = 0x01,			// 'auto': Scale to fit (non-borderless) or fill (borderless) if larger, otherwise center
  PAPPL_SCALING_AUTO_FIT = 0x02,		// 'auto-fit': Scale to fit if larger, otherwise center
  PAPPL_SCALING_FILL = 0x04,			// 'fill': Scale to fill the media
  PAPPL_SCALING_FIT = 0x08,			// 'fit': Scale to fit within margins
  PAPPL_SCALING_NONE = 0x10			// 'none': No scaling (center/crop)
};
typedef unsigned pappl_scaling_t;	// Bitfield for IPP "print-scaling" values

enum pappl_service_type_e		// IPP "printer-service-type" bit values
{
  PAPPL_SERVICE_TYPE_COPY = 0x01,		// 'copy'
  PAPPL_SERVICE_TYPE_FAXIN = 0x02,		// 'faxin'
  PAPPL_SERVICE_TYPE_FAXOUT = 0x04,		// 'faxout'
  PAPPL_SERVICE_TYPE_PRINT = 0x08,		// 'print'
  PAPPL_SERVICE_TYPE_PRINT3D = 0x10,		// 'print3d'
  PAPPL_SERVICE_TYPE_SCAN = 0x20,		// 'scan'
  PAPPL_SERVICE_TYPE_TRANSFORM = 0x40		// 'transform'
};
typedef unsigned pappl_service_type_t;	// Bitfield for IPP "printer-service-type" bit values

enum pappl_sides_e			// IPP "sides" bit values
{
  PAPPL_SIDES_ONE_SIDED = 0x01,			// 'one-sided'
  PAPPL_SIDES_TWO_SIDED_LONG_EDGE = 0x02,	// 'two-sided-long-edge'
  PAPPL_SIDES_TWO_SIDED_SHORT_EDGE = 0x04,	// 'two-sided-short-edge'
};
typedef unsigned pappl_sides_t;		// Bitfield for IPP "sides" values

typedef enum pappl_supply_color_e	// "printer-supply" color values
{
  PAPPL_SUPPLY_COLOR_NO_COLOR,			// No color (waste tank, etc.)
  PAPPL_SUPPLY_COLOR_BLACK,			// Black ink/toner (photo or matte)
  PAPPL_SUPPLY_COLOR_CYAN,			// Cyan ink/toner
  PAPPL_SUPPLY_COLOR_GRAY,			// Gray ink (sometimes marketed as light gray)
  PAPPL_SUPPLY_COLOR_GREEN,			// Green ink
  PAPPL_SUPPLY_COLOR_LIGHT_CYAN,		// Light cyan ink
  PAPPL_SUPPLY_COLOR_LIGHT_GRAY,		// Light gray ink (sometimes marketed as light light gray)
  PAPPL_SUPPLY_COLOR_LIGHT_MAGENTA,		// Light magenta ink
  PAPPL_SUPPLY_COLOR_MAGENTA,			// Magenta ink/toner
  PAPPL_SUPPLY_COLOR_ORANGE,			// Orange ink
  PAPPL_SUPPLY_COLOR_VIOLET,			// Violet ink
  PAPPL_SUPPLY_COLOR_YELLOW			// Yellow ink/toner
} pappl_supply_color_t;

typedef enum pappl_supply_type_e	// IPP "printer-supply" type values
{
  PAPPL_SUPPLY_TYPE_BANDING_SUPPLY,		// Banding finisher supplies
  PAPPL_SUPPLY_TYPE_BINDING_SUPPLY,		// Binding finisher supplies
  PAPPL_SUPPLY_TYPE_CLEANER_UNIT,		// Cleaning unit
  PAPPL_SUPPLY_TYPE_CORONA_WIRE,		// Corona wire (laser printers)
  PAPPL_SUPPLY_TYPE_COVERS,			// Cover finisher supplies
  PAPPL_SUPPLY_TYPE_DEVELOPER,			// Developer supply
  PAPPL_SUPPLY_TYPE_FUSER_CLEANING_PAD,		// Fuser cleaning pad (laser printers)
  PAPPL_SUPPLY_TYPE_FUSER_OIL_WICK,		// Fuser oil wick (laser printers)
  PAPPL_SUPPLY_TYPE_FUSER_OIL,			// Fuser oil supply (laser printers)
  PAPPL_SUPPLY_TYPE_FUSER_OILER,		// Fuser oiler (laser printers)
  PAPPL_SUPPLY_TYPE_FUSER,			// Fuser (laser printers)
  PAPPL_SUPPLY_TYPE_INK_CARTRIDGE,		// Ink cartridge
  PAPPL_SUPPLY_TYPE_INK_RIBBON,			// Ink ribbon supply
  PAPPL_SUPPLY_TYPE_INK,			// Ink supply
  PAPPL_SUPPLY_TYPE_INSERTS,			// Insert finisher supplies
  PAPPL_SUPPLY_TYPE_OPC,			// Optical photoconductor (laser printers)
  PAPPL_SUPPLY_TYPE_PAPER_WRAP,			// Wrap finisher supplies
  PAPPL_SUPPLY_TYPE_RIBBON_WAX,			// Wax ribbon supply
  PAPPL_SUPPLY_TYPE_SOLID_WAX,			// Solid wax supply
  PAPPL_SUPPLY_TYPE_STAPLES,			// Staple finisher supplies
  PAPPL_SUPPLY_TYPE_STITCHING_WIRE,		// Staple/stitch finisher supplies
  PAPPL_SUPPLY_TYPE_TONER_CARTRIDGE,		// Toner cartridge
  PAPPL_SUPPLY_TYPE_TONER,			// Toner supply
  PAPPL_SUPPLY_TYPE_TRANSFER_UNIT,		// Transfer unit (laser printers)
  PAPPL_SUPPLY_TYPE_WASTE_INK,			// Waste ink
  PAPPL_SUPPLY_TYPE_WASTE_TONER,		// Waste toner
  PAPPL_SUPPLY_TYPE_WASTE_WATER,		// Waste water
  PAPPL_SUPPLY_TYPE_WASTE_WAX,			// Waste wax
  PAPPL_SUPPLY_TYPE_WATER			// Water supply
} pappl_supply_type_t;


//
// Callback functions...
//

typedef void (*pappl_default_cb_t)(ipp_attribute_t *attr, void *data);
					// papplIterateDefaults callback function

typedef void (*pappl_identfunc_t)(pappl_printer_t *printer, pappl_identify_actions_t actions, const char *message);
					// Identify-Printer callback

typedef void (*pappl_job_cb_t)(pappl_job_t *job, void *data);
					// papplIterateXxxJobs callback function

typedef bool (*pappl_printfunc_t)(pappl_job_t *job, pappl_poptions_t *options, pappl_device_t *device);
					// Print a "raw" job callback
typedef bool (*pappl_rendjobfunc_t)(pappl_job_t *job, pappl_poptions_t *options, pappl_device_t *device);
					// End a raster job callback
typedef bool (*pappl_rendpagefunc_t)(pappl_job_t *job, pappl_poptions_t *options, pappl_device_t *device, unsigned page);
					// End a raster page callback
typedef bool (*pappl_rstartjobfunc_t)(pappl_job_t *job, pappl_poptions_t *options, pappl_device_t *device);
					// Start a raster job callback
typedef bool (*pappl_rstartpagefunc_t)(pappl_job_t *job, pappl_poptions_t *options, pappl_device_t *device, unsigned page);
					// Start a raster page callback
typedef bool (*pappl_rwritefunc_t)(pappl_job_t *job, pappl_poptions_t *options, pappl_device_t *device, unsigned y, const unsigned char *line);
					// Write a line of raster graphics callback
typedef bool (*pappl_statusfunc_t)(pappl_printer_t *printer);
					// Update printer status callback


//
// Structures...
//

typedef struct pappl_icon_s 		// Printer PNG icon structure
{
  char		filename[256];			// External filename, if any
  const void	*data;				// PNG icon data, if any
  size_t	datalen;			// Size of PNG icon data
} pappl_icon_t;

typedef struct pappl_media_col_s	// Media details structure
{
  int			bottom_margin,		// Bottom margin in hundredths of millimeters
			left_margin,		// Left margin in hundredths of millimeters
			left_offset,		// Left offset in hundredths of millimeters
			right_margin,		// Right margin in hundredths of millimeters
			size_width,		// Width in hundredths of millimeters
			size_length;		// Height in hundredths of millimeters
  char			size_name[64],		// PWG media size name
			source[64];		// PWG media source name
  int			top_margin,		// Top margin in hundredths of millimeters
			top_offset;		// Top offset in hundredths of millimeters
  pappl_media_tracking_t tracking;		// Media tracking
  char			type[64];		// PWG media type name
} pappl_media_col_t;

struct pappl_poptions_s			// Combined print job options
{
  cups_page_header2_t	header;			// Raster header
  unsigned		num_pages,		// Number of pages in job
			first_page,		// First page in page-ranges, starting at 1
			last_page;		// Last page in page-ranges, starting at 1
  pappl_dither_t	dither;			// Dither array, if any
  int			copies;	 		// "copies" value
  pappl_finishings_t	finishings;		// "finishings" value(s)
  pappl_media_col_t	media;			// "media"/"media-col" value
  ipp_orient_t		orientation_requested;	// "orientation-requested" value
  pappl_color_mode_t	print_color_mode;	// "print-color-mode" value
  pappl_content_t	print_content_optimize;	// "print-content-optimize" value
  int			print_darkness;		// "print-darkness" value
  int			darkness_configured;	// "printer-darkness-configured" value
  ipp_quality_t		print_quality;		// "print-quality" value
  pappl_scaling_t	print_scaling;		// "print-scaling" value
  int			print_speed;		// "print-speed" value
  int			printer_resolution[2];	// "printer-resolution" value in dots per inch
  pappl_sides_t		sides;			// "sides" value
};

typedef struct pappl_psupply_s		// Supply data
{
  pappl_supply_color_t	color;			// Color, if any
  char			description[256];	// Description
  bool			is_consumed;		// Is this a supply that is consumed?
  int			level;			// Level (0-100, -1 = unknown)
  pappl_supply_type_t	type;			// Type
} pappl_supply_t;

enum pappl_scan_color_modes			// IPP "input-color-mode" bit values extended for
{
  PAPPL_SCAN_COLOR_MODE_AUTO = 0x01,			// 'auto': 
  PAPPL_SCAN_COLOR_MODE_BILEVEL = 0x02,		// 'bi-level': 
  PAPPL_SCAN_COLOR_MODE_COLOR = 0x04,			// 'color': 
  PAPPL_SCAN_COLOR_MODE_MONO_4= 0x08,			// 'monochrome_4': 
  PAPPL_SCAN_COLOR_MODE_MONO_8 = 0x10			// 'monochrome_8': 
  PAPPL_SCAN_COLOR_MODE_MONO_16 = 0x20,			// 'monochrome_16':
  PAPPL_SCAN_COLOR_MODE_MONO = 0x40,		// 'monochrome':
  PAPPL_SCAN_COLOR_MODE_COLOR_8 = 0x80,			// 'color_8': 
  PAPPL_SCAN_COLOR_MODE_RGBA_8 = 0x100,			// 'rgba_8': 
  PAPPL_SCAN_COLOR_MODE_RGB_16 = 0x200			// 'rgb_16':
  PAPPL_SCAN_COLOR_MODE_RGBA_16 = 0x400,			// 'rgba_16': 
  PAPPL_SCAN_COLOR_MODE_CMYK_8 = 0x800,		// 'cmyk_8': 
  PAPPL_SCAN_COLOR_MODE_CMYK_16 = 0x1000,			// 'cmyk_16': 
};
typedef unsigned pappl_scan_color_modes_t;	// Bitfield for IPP "input-color-mode" values for scan

enum pappl_scan_content_type			// IPP "input-content-type" bit values
{
  PAPPL_SCAN_CONTENT_TYPE_AUTO = 0x01,			// 'auto': automatically determine the type of document
  PAPPL_SCAN_CONTENT_TYPE_HALFTONE = 0x02,		// 'halftone': automatically determine the type of document
  PAPPL_SCAN_CONTENT_TYPE_LINEART = 0x04,			// 'line-art': the document contains line art
  PAPPL_SCAN_CONTENT_TYPE_MAGAZINE= 0x08,			// 'magazine': the document is a magazine
  PAPPL_SCAN_CONTENT_TYPE_PHOTO = 0x10			// 'photo': the document is a photograph
  PAPPL_SCAN_CONTENT_TYPE_TEXT = 0x20,			// 'text': the document only contains text
  PAPPL_SCAN_CONTENT_TYPE_TEXT_PHOTO = 0x40,		// 'text-and-photo': the document contains a combination of text and photographs
};
typedef unsigned pappl_scan_content_type_t;	// Bitfield for IPP "input-content-type" values for scan

enum pappl_scan_film			// IPP "input-film-scan-mode" bit values
{
  PAPPL_SCAN_FILM_BW_NEG = 0x01,			// 'black-and-white-negative-film': The film is black-and-white negatives
  PAPPL_SCAN_FILM_COLOR_NEG = 0x02,		// 'color-negative-film': The film is color negatives
  PAPPL_SCAN_FILM_COLOR_SLIDE = 0x04,			// 'color-slide-film': The film is color slides (positives)
  PAPPL_SCAN_FILM_NA = 0x08,			// 'not-applicable': The type of film is not applicable to the usage
};
typedef unsigned pappl_scan_film_t;	// Bitfield for IPP "input-film-scan-mode" values for scan

typedef struct pappl_scan_region_s		// "input-scan-regions" values
{
  int   x_origin;   // "x-origin" values in 1/2540th of an inch.
  int   x_dim;   // "x-dim" values in 1/2540th of an inch.
  int   y_origin;   // "y-origin" values in 1/2540th of an inch.
  int   y_dim;   // "y-dim" values in 1/2540th of an inch.
} pappl_scan_region_t;

enum pappl_scan_input_source			// IPP "input-source" bit values
{
  PAPPL_SCAN_INPUT_SOURCE_ADF = 0x01,			// 'adf': scans documents from the auto-document feeder
  PAPPL_SCAN_INPUT_SOURCE_FILM_READER = 0x02,		// 'film-reader': scans documents from a microfilm reader
  PAPPL_SCAN_INPUT_SOURCE_PLATEN = 0x04,			// 'platen': scans a single page document from the scanner glass or platen
};
typedef unsigned pappl_scan_input_source_t;	// Bitfield for IPP "input-film-scan-mode" values for scan

typedef struct pappl_scan_region_s		// "input-scan-regions" values
{
  int   x_origin;   // "x-origin" values in 1/2540th of an inch.
  int   x_dim;   // "x-dim" values in 1/2540th of an inch.
  int   y_origin;   // "y-origin" values in 1/2540th of an inch.
  int   y_dim;   // "y-dim" values in 1/2540th of an inch.
} pappl_scan_region_t;


struct pappl_pdriver_data_s		// Print driver data
{
  pappl_identfunc_t	identify;		// Identify-Printer function
  pappl_printfunc_t	print;			// Print (file) function
  pappl_rendjobfunc_t	rendjob;		// End raster job function
  pappl_rendpagefunc_t	rendpage;		// End raster page function
  pappl_rstartjobfunc_t rstartjob;		// Start raster job function
  pappl_rstartpagefunc_t rstartpage;		// Start raster page function
  pappl_rwritefunc_t	rwrite;			// Write raster line function
  pappl_statusfunc_t	status;			// Status function
  pappl_dither_t	gdither;		// 'auto', 'text', and 'graphic' dither array
  pappl_dither_t	pdither;		// 'photo' dither array
  const char		*format;		// Printer-specific format
  char			make_and_model[128];	// "printer-make-and-model" value | "printer-make-and-model" values for scan
  int			ppm,			// "pages-per-minute" value
			ppm_color;		// "pages-per-minute-color" value, if any
  pappl_icon_t		icons[3];		// "printer-icons" values | "printer-icons" values for scan
  pappl_kind_t		kind;			// "printer-kind" values
  bool			has_supplies,		// Printer has supplies to report
			input_face_up,		// Does input media come in face-up?
			output_face_up;		// Does output media come out face-up?
  ipp_orient_t		orient_default;		// "orientation-requested-default" value | "input-orientation-requested" default value for scan
  pappl_color_mode_t	color_supported,	// "print-color-mode" values
			color_default;		// "print-color-mode-default" value
  pappl_content_t	content_default;	// "print-content-default" value
  ipp_quality_t		quality_default;	// "print-quality-default" value | "input-quality" default for scan
  pappl_scaling_t	scaling_default;	// "print-scaling-default" value
  pappl_raster_type_t	raster_types;		// "pwg-raster-document-type-supported" values
  pappl_raster_type_t	force_raster_type;	// Force a particular raster type?
  pappl_duplex_t	duplex;			// Duplex printing modes supported
  pappl_sides_t		sides_supported,	// "sides-supported" values | "input-sides" supported for scan
			sides_default;		// "sides-default" value  | "input-sides" supported for scan
  pappl_finishings_t	finishings;		// "finishings-supported" values
  int			num_resolution,		// Number of printer resolutions
			x_resolution[PAPPL_MAX_RESOLUTION],
			y_resolution[PAPPL_MAX_RESOLUTION],
						// Printer resolutions
			x_default,
			y_default;		// Default resolution
  bool			borderless;		// Borderless margins supported?
  int			left_right,		// Left and right margins in hundredths of millimeters
			bottom_top;		// Bottom and top margins in hundredths of millimeters
  int			num_media;		// Number of supported media
  const char		*media[PAPPL_MAX_MEDIA];// Supported media
  pappl_media_col_t	media_default,		// Default media
			media_ready[PAPPL_MAX_SOURCE];
						// Ready media
  int			num_source;		// Number of media sources (trays/rolls)
  const char		*source[PAPPL_MAX_SOURCE];
						// Media sources
  int			left_offset_supported[2],
						// media-left-offset-supported (0,0 for none)
			top_offset_supported[2];
						// media-top-offset-supported (0,0 for none)
  pappl_media_tracking_t tracking_supported;
						// media-tracking-supported
  int			num_type;		// Number of media types
  const char		*type[PAPPL_MAX_TYPE];	// Media types
  int			num_bin;		// Number of output bins
  const char		*bin[PAPPL_MAX_BIN];	// Output bins
  int			bin_default;		// Default output bin
  pappl_label_mode_t	mode_configured,	// label-mode-configured
			mode_supported;		// label-mode-supported
  int			tear_offset_configured,	// label-tear-offset-configured
			tear_offset_supported[2];
						// label-tear-offset-supported (0,0 for none)
  int			speed_supported[2],	// print-speed-supported (0,0 for none)
			speed_default;		// print-speed-default
  int			darkness_default,	// print-darkness-default
			darkness_configured,	// printer-darkness-configured
			darkness_supported;	// printer/print-darkness-supported (0 for none)
  pappl_identify_actions_t identify_default,	// "identify-actions-default" values
			identify_supported;	// "identify-actions-supported" values
  int			num_features;		// Number of "ipp-features-supported" values
  const char		*features[PAPPL_MAX_VENDOR];
						// "ipp-features-supported" values
  int			num_vendor;		// Number of vendor attributes
  const char		*vendor[PAPPL_MAX_VENDOR];
						// Vendor attribute names
  // Default Scanner Specific Attributes
  bool    scan_color_supported;  // "color-supported" value
  bool    input_auto_exposure_default,    // "input-auto-exposure" default values
      input_auto_scaling_default,   // "input-auto-scaling" default values
      input_auto_skew_correction_default;   // "input-auto-skew-correction" default values
  int    input_brightness_default;   // "input-brightness" default values (-100,100)
  pappl_scan_color_modes_t    input_color_mode_default;    // "input-color-mode" default values for scanner
  pappl_scan_content_type_t   input_content_type_default;   // "input-content-type" default values 
  int   input_contrast_default;   //  "input_contrast" default values (-100,100)
  pappl_scan_film_t   input_film_scan_mode_default;   // "input-film-scan-mode" default values 
  int   input_images_to_transfer_default,    // "input-images-to-transfer" default values
      input_scaling_height_default,   // "input-scaling-height" default values (1,1000)
      input_scaling_width_default;   // "input-scaling-width" default values (1,1000)
  pappl_scan_region_t   input_scan_regions_default;   // "input-scan-regions" default value
  int   input_sharpness_default;    // "input-sharpness" default value in (-100:100)
  pappl_scan_input_source_t   input_source_default;   //  "input-source" default value
  int   number_of_retries_default,    // "number-of-retries" default value
      noise_removal_default,    // output-attributes - "noise-removal" default value (0,100)
      output_compression_quality_factor_default,    // output-attributes - "output-compression-quality-factor" default value (0,100)
      retry_interval_default,   // "retry-interval" default values 
      retry_time_out_default;   // "retry-time-out" default values
  pwg_media_t   default_media;    // "input-media" default values 
};



//
// Functions...
//

extern void		papplPrinterAddLink(pappl_printer_t *printer, const char *label, const char *path_or_url, bool secure);

extern void		papplPrinterCancelAllJobs(pappl_printer_t *printer) _PAPPL_PUBLIC;

extern void		papplPrinterCloseDevice(pappl_printer_t *printer) _PAPPL_PUBLIC;

extern pappl_printer_t	*papplPrinterCreate(pappl_system_t *system, pappl_service_type_t type, int printer_id, const char *printer_name, const char *driver_name, const char *device_id, const char *device_uri) _PAPPL_PUBLIC;
extern void		papplPrinterDelete(pappl_printer_t *printer) _PAPPL_PUBLIC;

extern pappl_job_t	*papplPrinterFindJob(pappl_printer_t *printer, int job_id) _PAPPL_PUBLIC;

extern int		papplPrinterGetActiveJobs(pappl_printer_t *printer) _PAPPL_PUBLIC;
extern pappl_contact_t	*papplPrinterGetContact(pappl_printer_t *printer, pappl_contact_t *contact) _PAPPL_PUBLIC;
extern char		*papplPrinterGetDNSSDName(pappl_printer_t *printer, char *buffer, size_t bufsize) _PAPPL_PUBLIC;
extern char		*papplPrinterGetDriverName(pappl_printer_t *printer, char *buffer, size_t bufsize) _PAPPL_PUBLIC;
extern char		*papplPrinterGetGeoLocation(pappl_printer_t *printer, char *buffer, size_t bufsize) _PAPPL_PUBLIC;
extern int		papplPrinterGetID(pappl_printer_t *printer) _PAPPL_PUBLIC;
extern int		papplPrinterGetImpressionsCompleted(pappl_printer_t *printer) _PAPPL_PUBLIC;
extern char		*papplPrinterGetLocation(pappl_printer_t *printer, char *buffer, size_t bufsize) _PAPPL_PUBLIC;
extern int		papplPrinterGetMaxActiveJobs(pappl_printer_t *printer) _PAPPL_PUBLIC;
extern int		papplPrinterGetMaxCompletedJobs(pappl_printer_t *printer) _PAPPL_PUBLIC;
extern const char	*papplPrinterGetName(pappl_printer_t *printer) _PAPPL_PUBLIC;
extern int		papplPrinterGetNextJobID(pappl_printer_t *printer) _PAPPL_PUBLIC;
extern int		papplPrinterGetNumberOfActiveJobs(pappl_printer_t *printer) _PAPPL_PUBLIC;
extern int		papplPrinterGetNumberOfCompletedJobs(pappl_printer_t *printer) _PAPPL_PUBLIC;
extern int		papplPrinterGetNumberOfJobs(pappl_printer_t *printer) _PAPPL_PUBLIC;
extern char		*papplPrinterGetOrganization(pappl_printer_t *printer, char *buffer, size_t bufsize) _PAPPL_PUBLIC;
extern char		*papplPrinterGetOrganizationalUnit(pappl_printer_t *printer, char *buffer, size_t bufsize) _PAPPL_PUBLIC;
extern pappl_pdriver_data_t *papplPrinterGetPrintDriverData(pappl_printer_t *printer, pappl_pdriver_data_t *data) _PAPPL_PUBLIC;
extern char		*papplPrinterGetPrintGroup(pappl_printer_t *printer, char *buffer, size_t bufsize) _PAPPL_PUBLIC;
extern pappl_preason_t	papplPrinterGetReasons(pappl_printer_t *printer) _PAPPL_PUBLIC;
extern ipp_pstate_t	papplPrinterGetState(pappl_printer_t *printer) _PAPPL_PUBLIC;
extern int		papplPrinterGetSupplies(pappl_printer_t *printer, int max_supplies, pappl_supply_t *supplies) _PAPPL_PUBLIC;
extern pappl_system_t	*papplPrinterGetSystem(pappl_printer_t *printer) _PAPPL_PUBLIC;
extern pappl_service_type_t papplPrinterGetType(pappl_printer_t *printer) _PAPPL_PUBLIC;

extern void		papplPrinterIterateActiveJobs(pappl_printer_t *printer, pappl_job_cb_t cb, void *data, int first_index, int limit) _PAPPL_PUBLIC;
extern void		papplPrinterIterateAllJobs(pappl_printer_t *printer, pappl_job_cb_t cb, void *data, int first_index, int limit) _PAPPL_PUBLIC;
extern void		papplPrinterIterateCompletedJobs(pappl_printer_t *printer, pappl_job_cb_t cb, void *data, int first_index, int limit) _PAPPL_PUBLIC;

extern pappl_device_t	*papplPrinterOpenDevice(pappl_printer_t *printer) _PAPPL_PUBLIC;

extern void		papplPrinterSetContact(pappl_printer_t *printer, pappl_contact_t *contact) _PAPPL_PUBLIC;
extern void		papplPrinterSetDNSSDName(pappl_printer_t *printer, const char *value) _PAPPL_PUBLIC;
extern void		papplPrinterSetGeoLocation(pappl_printer_t *printer, const char *value) _PAPPL_PUBLIC;
extern void		papplPrinterSetImpressionsCompleted(pappl_printer_t *printer, int add) _PAPPL_PUBLIC;
extern void		papplPrinterSetLocation(pappl_printer_t *printer, const char *value) _PAPPL_PUBLIC;
extern void		papplPrinterSetMaxActiveJobs(pappl_printer_t *printer, int max_active_jobs) _PAPPL_PUBLIC;
extern void		papplPrinterSetMaxCompletedJobs(pappl_printer_t *printer, int max_completed_jobs) _PAPPL_PUBLIC;
extern void		papplPrinterSetNextJobID(pappl_printer_t *printer, int next_job_id) _PAPPL_PUBLIC;
extern void		papplPrinterSetOrganization(pappl_printer_t *printer, const char *value) _PAPPL_PUBLIC;
extern void		papplPrinterSetOrganizationalUnit(pappl_printer_t *printer, const char *value) _PAPPL_PUBLIC;
extern void		papplPrinterSetPrintDefaults(pappl_printer_t *printer, pappl_pdriver_data_t *data) _PAPPL_PUBLIC;
extern void		papplPrinterSetPrintDriverData(pappl_printer_t *printer, pappl_pdriver_data_t *data, ipp_t *attrs) _PAPPL_PUBLIC;
extern void		papplPrinterSetPrintGroup(pappl_printer_t *printer, const char *value) _PAPPL_PUBLIC;
extern void		papplPrinterSetReadyMedia(pappl_printer_t *printer, int num_ready, pappl_media_col_t *ready) _PAPPL_PUBLIC;
extern void		papplPrinterSetReasons(pappl_printer_t *printer, pappl_preason_t add, pappl_preason_t remove) _PAPPL_PUBLIC;
extern void		papplPrinterSetSupplies(pappl_printer_t *printer, int num_supplies, pappl_supply_t *supplies) _PAPPL_PUBLIC;

//
// C++ magic...
//

#  ifdef __cplusplus
}
#  endif // __cplusplus


#endif // !_PAPPL_PRINTER_H_
