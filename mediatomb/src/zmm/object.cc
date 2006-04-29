/*  object.cc - this file is part of MediaTomb.
                                                                                
    Copyright (C) 2005 Gena Batyan <bgeradz@deadlock.dhs.org>,
                       Sergey Bostandzhyan <jin@deadlock.dhs.org>
                                                                                
    MediaTomb is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.
                                                                                
    MediaTomb is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
                                                                                
    You should have received a copy of the GNU General Public License
    along with MediaTomb; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#include <stdio.h>
#include <malloc.h>

#include "object.h"
#include "memory.h"

using namespace zmm;

Object::Object()
{
	_ref_count = 0;
}
Object::~Object()
{}

void Object::retain()
{
	_ref_count++;
}
void Object::release()
{
	_ref_count--;
	if(_ref_count == 0)
	{
		delete this;
	}
}

int Object::getRefCount()
{
    return _ref_count;
}

void* Object::operator new (size_t size)
{
    return MALLOC(size);
}
void Object::operator delete (void *ptr)
{
    FREE(ptr);
}
