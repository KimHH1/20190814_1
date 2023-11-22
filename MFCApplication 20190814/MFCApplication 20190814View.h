
// MFCApplication 20190814View.h: CMFCApplication20190814View 클래스의 인터페이스
//

#pragma once


class CMFCApplication20190814View : public CScrollView
{
protected: // serialization에서만 만들어집니다.
	CMFCApplication20190814View() noexcept;
	DECLARE_DYNCREATE(CMFCApplication20190814View)

// 특성입니다.
public:
	CMFCApplication20190814Doc* GetDocument() const;

// 작업입니다.
public:

// 재정의입니다.
public:
	virtual void OnDraw(CDC* pDC);  // 이 뷰를 그리기 위해 재정의되었습니다.
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CMFCApplication20190814View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPixeladd();
	afx_msg void OnPixelmul();
	afx_msg void OnPixelsub();
	afx_msg void OnPixeldiv();
	afx_msg void OnPixelHistoEq();
	afx_msg void OnPixelContrastStretching();
	afx_msg void OnPixelBinarization();
	afx_msg void OnPixelTwoImageAdd();
	void LoadTwoImage();
	afx_msg void OnPixelTwoImageSub();
	afx_msg void OnRegionSmoothing();
	void Convolve(unsigned char ** InImg, unsigned char ** OutImg, int cols, int rows, float mask[][3], int bias, int depth);
	afx_msg void OnRegionSharpening();
	afx_msg void OnRegionEmbossing();
	afx_msg void OnRegionPrewitt();
	afx_msg void OnRegionRoberts();
	afx_msg void OnRegionSobel();
	afx_msg void OnRegionAverageFiltering();
	afx_msg void OnRegionMedianFiltering();
	afx_msg void OnMopologyColorGray();
	afx_msg void OnMopologyBinarization();
	afx_msg void OnMopologyErosion();
	afx_msg void OnMopologyDilation();
	afx_msg void OnMopologyOpening();
	void CopyResultToinput();
	afx_msg void OnMopologyClosing();
	afx_msg void OnGeometryZoominPixelCopy();
	afx_msg void OnGeometryZoominBilinearInterpolation();
	afx_msg void OnGeometryZoomoutSubsampling();
	afx_msg void OnGeometryZoomoutMeanSub();
	afx_msg void OnGeometryAvgFiltering();
	afx_msg void OnGeometryRotation();
	afx_msg void OnGeometryHolizantialFup();
	afx_msg void OnGeometryVerticalFup();
	afx_msg void OnGeobetryWarping();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};

#ifndef _DEBUG  // MFCApplication 20190814View.cpp의 디버그 버전
inline CMFCApplication20190814Doc* CMFCApplication20190814View::GetDocument() const
   { return reinterpret_cast<CMFCApplication20190814Doc*>(m_pDocument); }
#endif

