extern helpMenuInfo *TSPlotHelp[], *XYPlotHelp[], *XYSortHelp[];
extern helpMenuInfo *Scat2DHelp[], *Scat3DHelp[];
extern helpMenuInfo *Hist1DHelp[], *Hist1DAHelp[];
extern helpMenuInfo *Hist2DHelp[], *Hist2DAHelp[];
extern helpMenuInfo *CellHelp[], *OverlayHelp[];
extern helpMenuInfo *TSPlotHelpM[], *XYPlotHelpM[], *XYSortHelpM[];
extern helpMenuInfo *Scat2DHelpM[], *Scat3DHelpM[];
extern helpMenuInfo *Hist1DHelpM[], *Hist1DAHelpM[], *OverlayHelpM[];
extern helpMenuInfo *Hist2DHelpM[], *Hist2DAHelpM[];
extern helpMenuInfo *CellHelpM[]; 
extern helpMenuInfo *IndicatorHelp[], *NPlotHelp[];
extern helpMenuInfo *ControlHelp[], *TriggerHelp[];
extern helpMenuInfo *CapMainMenuHelp[], *MainMenuHelp[];
    
void AutoHelp2D(Widget parent);
void AutoHelp3D(Widget parent);
void AutoHelp2DHist(Widget parent);
void NtuplePanelHelpCB(Widget widget, caddr_t client_data, caddr_t call_data);
void VariablePanelHelpCB(Widget w, caddr_t clientData, caddr_t callData);
void TimeSeriesHelpCB(Widget widget, caddr_t client_data, caddr_t call_data);
void XYHelpCB(Widget widget, caddr_t client_data, caddr_t call_data);
void XYSortHelpCB(Widget widget, caddr_t client_data, caddr_t call_data);
void Scat2DHelpCB(Widget widget, caddr_t client_data, caddr_t call_data);
void Scat3DHelpCB(Widget widget, caddr_t client_data, caddr_t call_data);
void Hist1DHelpCB(Widget widget, caddr_t client_data, caddr_t call_data);
void Hist2DHelpCB(Widget widget, caddr_t client_data, caddr_t call_data);
void Hist1DAHelpCB(Widget widget, caddr_t client_data, caddr_t call_data);
void Hist2DAHelpCB(Widget widget, caddr_t client_data, caddr_t call_data);
void CellHelpCB(Widget widget, caddr_t client_data, caddr_t call_data);
void IndicatorHelpCB(Widget widget, caddr_t client_data, caddr_t call_data);
void TriggerHelpCB(Widget widget, caddr_t client_data, caddr_t call_data);
void ControlHelpCB(Widget widget, caddr_t client_data, caddr_t call_data);
