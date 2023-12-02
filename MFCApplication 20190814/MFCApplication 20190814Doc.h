
// MFCApplication 20190814Doc.h: CMFCApplication20190814Doc 클래스의 인터페이스
//


#pragma once


class CMFCApplication20190814Doc : public CDocument
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication20190814Doc() noexcept;
	DECLARE_DYNCREATE(CMFCApplication20190814Doc)

// 특성입니다.
public:

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 구현입니다.
public:
	virtual ~CMFCApplication20190814Doc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 검색 처리기에 대한 검색 콘텐츠를 설정하는 도우미 함수
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	unsigned char **InPutImg;			//[y][x]
	unsigned char **InPutImg2;			//[y][x]
	unsigned char **ResultImg;			//[y][x]
	int ImageWidth;
	int ImageHeight;
	int depth;		//흑백=1, 칼라=3

	int gImageWidth;
	int gImageHeight;

	unsigned char **gResultImg;			//[y][x]
	unsigned char **morphedImg[10];

	void LoadImageFile(CArchive& ar);
	void LoadSecondImageFile(CArchive & ar);
};
