/**
 *
 * $Id: VendorSP.h,v 1.4 2001/09/13 12:28:18 amai Exp $
 *
 * Copyright (C) 1995 Free Software Foundation, Inc.
 * Copyright (C) 1995-2000 LessTif Development Team
 *
 * This file is part of the GNU LessTif Library.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the Free
 * Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 **/

#ifndef _XM_VENDORSP_H
#define _XM_VENDORSP_H

#include <Xm/XmP.h>
#include <Xm/VendorS.h>
#include <X11/ShellP.h>

#ifdef __cplusplus
extern "C" {
#endif

extern Cardinal _XmFilterResources(XtResource *resources,
				   Cardinal numResources,
				   WidgetClass filterClass,
				   XtResource **filteredResourcesRtn);

extern void _XmAddGrab(Widget wid,
		       Boolean exclusive,
		       Boolean spring_loaded);

extern void _XmRemoveGrab(Widget wid);

extern XtGeometryResult _XmRootGeometryManager(Widget w,
					       XtWidgetGeometry *request,
					       XtWidgetGeometry *reply);

extern void _XmVendorExtRealize(Widget w,
				XtPointer closure,
				XtPointer call_data) ;

extern Display *_XmGetDefaultDisplay(void);

extern VendorShellClassRec  vendorShellClassRec;


#ifdef __cplusplus
}
#endif

#endif /* _XM_VENDORSP_H */
