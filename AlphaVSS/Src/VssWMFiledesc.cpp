/* Copyright (c) 2008 Peter Palotas
 *  
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *  
 *  The above copyright notice and this permission notice shall be included in
 *  all copies or substantial portions of the Software.
 *  
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *  THE SOFTWARE.
 */
#include "StdAfx.h"

#include "VssWMFiledesc.h"

namespace Alphaleonis { namespace Win32 { namespace Vss
{
	VssWMFiledesc^ VssWMFiledesc::Adopt(IVssWMFiledesc *vssWMFiledesc)
	{
		return gcnew VssWMFiledesc(vssWMFiledesc);
	}

	VssWMFiledesc::VssWMFiledesc(IVssWMFiledesc *vssWMFiledesc)
	{
		try
		{
			AutoBStr bstrAlternateLocation;
			CheckCom(vssWMFiledesc->GetAlternateLocation(&bstrAlternateLocation));

#if NTDDI_VERSION >= NTDDI_LONGHORN
			DWORD dwTypeMask;
			CheckCom(vssWMFiledesc->GetBackupTypeMask(&dwTypeMask));
			mBackupTypeMask = (VssFileSpecBackupType)dwTypeMask;
#endif
			AutoBStr bstrFilespec;
			CheckCom(vssWMFiledesc->GetFilespec(&bstrFilespec));
			AutoBStr bstrPath;
			CheckCom(vssWMFiledesc->GetPath(&bstrPath));
			bool bRecursive;
			CheckCom(vssWMFiledesc->GetRecursive(&bRecursive));

			mAlternateLocation = bstrAlternateLocation;
			mFileSpec = bstrFilespec;
			mPath = bstrPath;
			mRecursive = bRecursive;
		}
		finally
		{
			vssWMFiledesc->Release();
		}

	}

	VssWMFiledesc::~VssWMFiledesc()
	{
	}

	String^ VssWMFiledesc::AlternateLocation::get()
	{
		return mAlternateLocation;
	}

	VssFileSpecBackupType VssWMFiledesc::BackupTypeMask::get()
	{
#if NTDDI_VERSION < NTDDI_WS03
		return mBackupTypeMask;
#else
		throw gcnew NotSupportedException(L"This method is not supported in Windows XP");
#endif
	}

	String^ VssWMFiledesc::FileSpec::get()
	{
		return mFileSpec;
	}

	String^ VssWMFiledesc::Path::get()
	{
		return mPath;
	}

	bool VssWMFiledesc::IsRecursive::get()
	{
		return mRecursive;
	}


}
} }