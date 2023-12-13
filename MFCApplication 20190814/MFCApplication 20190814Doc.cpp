
// MFCApplication 20190814Doc.cpp: CMFCApplication20190814Doc 클래스의 구현
//

#include "pch.h"
#include "framework.h"

// SHARED_HANDLERS는 미리 보기, 축소판 그림 및 검색 필터 처리기를 구현하는 ATL 프로젝트에서 정의할 수 있으며
// 해당 프로젝트와 문서 코드를 공유하도록 해 줍니다.
#ifndef SHARED_HANDLERS
#include "MFCApplication 20190814.h"
#endif

#include "MFCApplication 20190814Doc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMFCApplication20190814Doc

IMPLEMENT_DYNCREATE(CMFCApplication20190814Doc, CDocument)

BEGIN_MESSAGE_MAP(CMFCApplication20190814Doc, CDocument)
END_MESSAGE_MAP()


// CMFCApplication20190814Doc 생성/소멸

CMFCApplication20190814Doc::CMFCApplication20190814Doc() noexcept
{
	InPutImg = NULL;
	InPutImg2 = NULL;
	ResultImg = NULL;
	gResultImg = NULL;
}

CMFCApplication20190814Doc::~CMFCApplication20190814Doc()
{
	if (InPutImg != NULL)
	{
		for (int i = 0; i < ImageHeight; i++)
			free(InPutImg[i]);
		free(InPutImg);
	}
	if (InPutImg2 != NULL)
	{
		for (int i = 0; i < ImageHeight; i++)
			free(InPutImg2[i]);
		free(InPutImg2);
	}
	if (ResultImg != NULL)
	{
		for (int i = 0; i < ImageHeight; i++)
			free(ResultImg[i]);
		free(ResultImg);
	}
	if (gResultImg != NULL)
	{
		for (int i = 0; i < gImageHeight; i++)
			free(gResultImg[i]);
		free(gResultImg);
	}
}

BOOL CMFCApplication20190814Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMFCApplication20190814Doc serialization

void CMFCApplication20190814Doc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		LoadImageFile(ar);

	}
}

#ifdef SHARED_HANDLERS

// 축소판 그림을 지원합니다.
void CMFCApplication20190814Doc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 문서의 데이터를 그리려면 이 코드를 수정하십시오.
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT) GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 검색 처리기를 지원합니다.
void CMFCApplication20190814Doc::InitializeSearchContent()
{
	CString strSearchContent;
	// 문서의 데이터에서 검색 콘텐츠를 설정합니다.
	// 콘텐츠 부분은 ";"로 구분되어야 합니다.

	// 예: strSearchContent = _T("point;rectangle;circle;ole object;");
	SetSearchContent(strSearchContent);
}

void CMFCApplication20190814Doc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl *pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CMFCApplication20190814Doc 진단

#ifdef _DEBUG
void CMFCApplication20190814Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMFCApplication20190814Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMFCApplication20190814Doc 명령


void CMFCApplication20190814Doc::LoadImageFile(CArchive& ar)
{
	int maxValue;
	char type[16],buf[256];
	CFile *fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isbmp = false;

	if(strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strchr(fname,'.'),".pgm") == 0 || strcmp(strchr(fname,'.'),".PGM") == 0)
	{
		ar.ReadString(type, 15);
		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &ImageWidth, &ImageHeight);

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0)	depth = 1;
		else							depth = 3;
	}
	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0)
	{
		//bitmap file header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));
		if (bmfh.bfType != (WORD)('B' | ('M' << 8)))	return;

		//bitmap info header 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih,sizeof(bih));
		ImageWidth = bih.biWidth;
		ImageHeight = bih.biHeight;
		depth = bih.biBitCount / 8; //depth는 byte 단위고 biBitCount는 비트 단위라 8로 나눔

		if (depth == 1)
		{	//palette가 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}
		
		isbmp = true;
	}
	else if (strcmp(strchr(fname, '.'),".raw") == 0 || strcmp(strchr(fname, '.'),".RAW")==0 )
	{
		if (fp->GetLength() != 256 * 256)
		{
			AfxMessageBox("256*256 크기의 raw 파일만 사용가능합니다.");
			return;
		}

		ImageWidth = 256;
		ImageHeight = 256;
		depth = 1;
	}

	//메모리 할당
	InPutImg = (unsigned char **)malloc(ImageHeight * sizeof(unsigned char *));
	ResultImg = (unsigned char **)malloc(ImageHeight * sizeof(unsigned char *));
	for (int i = 0; i < ImageHeight; i++)
	{
		InPutImg[i]=(unsigned char*)malloc(ImageWidth*depth);
		ResultImg[i] = (unsigned char*)malloc(ImageWidth*depth);
	}

	//영상데이터 읽기
	if (!isbmp)
	{
		for (int i = 0; i < ImageHeight; i++)
			ar.Read(InPutImg[i], ImageWidth*depth);
	}
	else
	{
		//파일에서 읽어서 저장
		BYTE nu[4*3];
		int widthfile;
		widthfile = (ImageWidth * 8 + 31) / 32 * 4; //비트 수 계산
		for (int j = 0; j < ImageHeight; j++)
		{
			if(depth==1)
				ar.Read(InPutImg[ImageHeight-1-j], ImageWidth*depth);
			else
			{
				for (int i = 0; i < ImageWidth; i++) //BGR를 RGB로 변환
				{
					BYTE r, g, b;
					ar.Read(&b, 1), ar.Read(&g, 1), ar.Read(&r, 1);

					InPutImg[ImageHeight - 1 - j][3 * i + 0] = r;
					InPutImg[ImageHeight - 1 - j][3 * i + 1] = g;
					InPutImg[ImageHeight - 1 - j][3 * i + 2] = b;
				}
			}
			if ((widthfile - ImageWidth) != 0) //이 부분을 추가해야 사선으로 나오지 않음
			{
				ar.Read(nu, (widthfile - ImageWidth)*depth);
			}
		}
	}
}


void CMFCApplication20190814Doc::LoadSecondImageFile(CArchive & ar)
{
	int maxValue;
	char type[16], buf[256];
	CFile *fp = ar.GetFile();
	CString fname = fp->GetFilePath();
	bool isbmp = false;
	
	int imgw, imgh, imgd;

	if (strcmp(strchr(fname, '.'), ".ppm") == 0 || strcmp(strchr(fname, '.'), ".PPM") == 0 ||
		strcmp(strchr(fname, '.'), ".pgm") == 0 || strcmp(strchr(fname, '.'), ".PGM") == 0)
	{
		ar.ReadString(type, 15);
		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d %d", &imgw, &imgh);

		do {
			ar.ReadString(buf, 256);
		} while (buf[0] == '#');
		sscanf_s(buf, "%d", &maxValue);

		if (strcmp(type, "P5") == 0)	imgd = 1;
		else							imgd = 3;
	}

	else if (strcmp(strchr(fname, '.'), ".bmp") == 0 || strcmp(strchr(fname, '.'), ".BMP") == 0)
	{
		//bitmap file header 읽기
		BITMAPFILEHEADER bmfh;
		ar.Read((LPSTR)&bmfh, sizeof(bmfh));
		if (bmfh.bfType != (WORD)('B' | ('M' << 8)))	return;

		//bitmap info header 읽기
		BITMAPINFOHEADER bih;
		ar.Read((LPSTR)&bih, sizeof(bih));
		imgw = bih.biWidth; //위에 한 것과 동일한데 이름을 InPutImg2에서 사용하는 이름으로 바꿈
		imgh = bih.biHeight;
		imgd = bih.biBitCount / 8; //depth는 byte 단위고 biBitCount는 비트 단위라 8로 나눔

		if (imgd == 1)
		{	//palette가 존재
			BYTE palette[256 * 4];
			ar.Read(palette, 256 * 4);
		}

		isbmp = true;
	}
	else if (strcmp(strchr(fname, '.'), ".raw") == 0 || strcmp(strchr(fname, '.'), ".RAW") == 0)
	{
		if (fp->GetLength() != 256 * 256)
		{
			AfxMessageBox("256*256 크기의 raw 파일만 사용가능합니다.");
			return;
		}

		imgw = 256;
		imgh = 256;
		imgd = 1;
	}

	if (imgw != ImageWidth || imgh != ImageHeight || imgd != depth)
	{
		AfxMessageBox("동일한 크기의 화일만 읽어들일수 있습니다.");
		return;
	}

	//메모리 할당
	InPutImg2 = (unsigned char **)malloc(ImageHeight * sizeof(unsigned char *));
	for (int i = 0; i < ImageHeight; i++)
	{
		InPutImg2[i] = (unsigned char*)malloc(ImageWidth*depth);
	}

	//영상데이터 읽기
	if (!isbmp)
	{
		for (int i = 0; i < ImageHeight; i++)
			ar.Read(InPutImg2[i], ImageWidth*depth);
	}
	else
	{
		//파일에서 읽어서 저장
		BYTE nu[4 * 3];
		int widthfile;
		widthfile = (ImageWidth * 8 + 31) / 32 * 4; //비트 수 계산
		for (int j = 0; j < ImageHeight; j++)
		{
			if (depth == 1)
				ar.Read(InPutImg2[ImageHeight - 1 - j], ImageWidth*depth);
			else
			{
				for (int i = 0; i < ImageWidth; i++) //BGR를 RGB로 변환
				{
					BYTE r, g, b;
					ar.Read(&b, 1), ar.Read(&g, 1), ar.Read(&r, 1);

					InPutImg2[ImageHeight - 1 - j][3 * i + 0] = r;
					InPutImg2[ImageHeight - 1 - j][3 * i + 1] = g;
					InPutImg2[ImageHeight - 1 - j][3 * i + 2] = b;
				}
			}
			if ((widthfile - ImageWidth) != 0) //이 부분을 추가해야 사선으로 나오지 않음
			{
				ar.Read(nu, (widthfile - ImageWidth)*depth);
			}
		}
	}
}
