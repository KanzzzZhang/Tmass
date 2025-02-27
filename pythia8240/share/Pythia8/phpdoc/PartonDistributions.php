<html>
<head>
<title>Parton Distributions</title>
<link rel="stylesheet" type="text/css" href="pythia.css"/>
<link rel="shortcut icon" href="pythia32.gif"/>
</head>
<body>

<script language=javascript type=text/javascript>
function stopRKey(evt) {
var evt = (evt) ? evt : ((event) ? event : null);
var node = (evt.target) ? evt.target :((evt.srcElement) ? evt.srcElement : null);
if ((evt.keyCode == 13) && (node.type=="text"))
{return false;}
}

document.onkeypress = stopRKey;
</script>
<?php
if($_POST['saved'] == 1) {
if($_POST['filepath'] != "files/") {
echo "<font color='red'>SETTINGS SAVED TO FILE</font><br/><br/>"; }
else {
echo "<font color='red'>NO FILE SELECTED YET.. PLEASE DO SO </font><a href='SaveSettings.php'>HERE</a><br/><br/>"; }
}
?>

<form method='post' action='PartonDistributions.php'>
 
<h2>Parton Distributions</h2> 
 
The parton distributions file contains the <code>PDF</code> class. 
<code>PDF</code> is the base class, from which specific <code>PDF</code> 
classes are derived. 
 
<p/> 
The choice of which PDF to use is made by settings in the 
<code>Pythia</code> class, see <?php $filepath = $_GET["filepath"];
echo "<a href='PDFSelection.php?filepath=".$filepath."' target='page'>";?>here</a>. 
These settings also allow to access all the proton PDF's available in the 
LHAPDF library [<a href="Bibliography.php#refWha05" target="page">Wha05</a>,<a href="Bibliography.php#refBuc15" target="page">Buc15</a>]. Thus there is no need for a normal 
user to study the <code>PDF</code> class. The structure must only be 
understood when interfacing new PDF's, e.g. ones not yet found in LHAPDF. 
 
<a name="section0"></a> 
<h3>The PDF base class</h3> 
 
<code>PDF</code> defines the interface that all PDF classes should respect. 
The constructor requires the incoming beam species to be given: 
even if used for a proton PDF, one needs to know whether the beam 
is actually an antiproton. This is one of the reasons why <code>Pythia</code> 
always defines two PDF objects in an event, one for each beam. 
 
<p/> 
Once a <code>PDF</code> object has been constructed, call it <code>pdf</code>, 
the main method is <code>pdf.xf( id, x, Q2)</code>, which returns 
<i>x*f_id(x, Q2)</i>, properly taking into account whether the beam 
is an antiparticle or not. 
 
<p/> 
Whenever the <code>xf</code> member is called with a new flavour, <i>x</i> 
or <i>Q^2</i>, the <code>xfUpdate</code> member is called to do the actual 
updating. This routine may either update that particular flavour or all 
flavours at this <i>(x, Q^2)</i> point. (In the latter case the saved 
<code>id</code> value <code>idSav</code> should be set to 9.) The choice is 
to be made by the producer of a given set, based on what he/she deems most 
effective, given that sometimes only one flavour need be evaluated, and 
about equally often all flavours are needed at the same <i>x</i> and 
<i>Q^2</i>. Anyway, the latest value is always kept in memory. This is 
the other reason why <code>Pythia</code> has one separate <code>PDF</code> 
object for each beam, so that values at different <i>x</i> can be kept 
in memory. 
 
<p/> 
Two further public methods are <code>xfVal( id, x, Q2)</code> and 
<code>xfSea( id, x, Q2)</code>. These are simple variants whereby 
the quark distributions can be subdivided into a valence and a sea part. 
If these are not directly accessible in the parametrization, one can 
make the simplified choices <i>u_sea = ubar_sea, u_val = u_tot - u_sea</i>, 
and correspondingly for <i>d</i>. (Positivity will always be guaranteed 
at output.) The <code>xfUpdate</code> method should also take care of 
updating this information. 
 
<p/> 
A method <code>setExtrapolate(bool)</code> allows you to switch between 
freezing parametrizations  at the low-<i>x</i> boundary 
(<code>false</code>) or extrapolate them outside the boundary 
(<code>true</code>). This method works both for LHAPDF 5, LHAPDF6 and 
modern internal PDFs. (For some older PDFs the behaviour implemented by 
the original authors is maintained.) In either case the PDFs are frozen 
at <i>Q_min</i> and <i>Q_max</i>. (And also at <i>x_max</i>, but 
this is irrelevant when <i>x_max = 1</i>.) 
 
<p/> 
With <code>insideBounds(double x, double Q2)</code> you can probe whether 
an <i>(x, Q^2)</i> pair falls inside the fit region or not. The 
<code>alphaS(double Q2)</code> method returns the <i>alpha_s</i> of the 
PDF at the given <i>Q^2</i> scale, while <code>mQuarkPDF(int id)</code> 
returns the quark masses used to set flavour thresholds. Currently these 
three methods are only implemented for LHAPDF6. 
 
<a name="section1"></a> 
<h3>Derived classes</h3> 
 
There is only one pure virtual method, <code>xfUpdate</code>, that 
therefore must be implemented in any derived class. A reasonable 
number of such classes come with the program: 
 
<p/> 
For protons: 
<ul> 
<li><code>LHAPDF</code> provides a plugin interface class to the 
LHAPDF library[<a href="Bibliography.php#refWha05" target="page">Wha05</a>,<a href="Bibliography.php#refBuc15" target="page">Buc15</a>]. It loads either the 
<code>LHAPDF5</code> or <code>LHAPDF6</code> class.</li> 
<li><code>GRV94L</code> gives the GRV 94 L parametrization 
[<a href="Bibliography.php#refGlu95" target="page">Glu95</a>].</li> 
<li><code>CTEQ5L</code> gives the CTEQ 5 L parametrization 
[<a href="Bibliography.php#refLai00" target="page">Lai00</a>].</li> 
<li><code>MSTWpdf</code> gives the four distributions of the 
MRST/MSTW group that have been implemented.</li> 
<li><code>CTEQ6pdf</code> gives the six distributions of the 
CTEQ/CT group that have been implemented.</li> 
<li><code>NNPDF</code> gives four distributions from the NNPDF 2.3 
QCD+QED sets that have been implemented.</li> 
<li><code>LHAGrid1</code> can read and use files in the LHAPDF6 lhagrid1 
format, assuming that the same x grid is used for all Q subgrids. 
Results are not exactly identical with LHAPDF6, owing to different 
interpolation.</li> 
<li><code>nPDF, Isospin, EPS09</code> three classes allowing to introduce 
nuclear modifications to a specified proton PDF. The first is base class 
for the other two, where <code>Isospin</code> only provides the 
appropriate mix of protons and isospin-conjugate neutrons, while 
<code>EPS09</code> also contains nuclear modification factors 
[<a href="Bibliography.php#refEsk09" target="page">Esk09</a>].</li> 
</ul> 
The current default is NNPDF 2.3. 
 
<p/> 
For charged pions: 
<ul> 
<li><code>GRVpiL</code> gives the GRV 1992 pi+ parametrization.</li> 
</ul> 
 
<p/> 
For Pomerons (used to describe diffraction): 
<ul> 
<li><code>PomFix</code> gives a simple but flexible 
<i>Q2</i>-independent parametrization.</li> 
<li><code>PomH1FitAB</code> gives the H1 2006 Fit A and Fit B 
parametrizations.</li> 
<li><code>PomH1Jets</code> gives the H1 2007 Jets parametrization.</li> 
</ul> 
 
<p/> 
For photons: 
<ul> 
<li><code>CJKL</code> gives the CJKL parametrization [<a href="Bibliography.php#refCor03" target="page">Cor03</a>].</li> 
<li><code>GammaPoint</code> gives the trivial distribution of a 
pointlike (i.e. unresolved) photon.</li> 
</ul> 
 
<p/> 
For charged leptons (e, mu, tau) and the proton: 
<ul> 
<li><code>Lepton</code> gives a QED parametrization [<a href="Bibliography.php#refKle89" target="page">Kle89</a>]. 
In QED there are not so many ambiguities, so here one set should be 
enough. On the other hand, there is the problem that the 
lepton-inside-lepton pdf is integrably divergent for <i>x &rarr; 1</i>, 
which gives numerical problems. Like in PYTHIA 6, the pdf is therefore 
made to vanish for <i>x > 1 - 10^{-10}</i>, and scaled up in the range 
<i>1 - 10^{-7} &lt; x &lt; 1 - 10^{-10}</i> in such a way that the 
total area under the pdf is preserved.</li> 
<li><code>LeptonPoint</code> gives the trivial distribution of a 
pointlike (i.e. unresolved) charged lepton.</li> 
<li><code>EPAexternal</code> provides an external photon flux to study 
photoproduction with different fluxes. Still optimized for lepton beams, 
but also other fluxes can be studied.</li> 
<li><code>Lepton2gamma</code> gives the convolution between photon 
flux from leptons and photon PDFs.</li> 
<li><code>ProtonPoint</code> gives the equivalent photon spectrum 
of an unresolved proton.</li> 
</ul> 
 
<p/> 
For neutrinos: 
<ul> 
<li><code>NeutrinoPoint</code> is the only method, so there is no choice. 
Analogously to <code>LeptonPoint</code> it gives the distribution of a 
pointlike (i.e. unresolved) neutrino. A difference, however, is that 
neutrinos always are lefthanded, so there is no need to average over 
incoming spin states. Since the PYTHIA formalism assumes unpolarized 
beams, and thus implicitly includes a 1/2 for incoming fermions, the 
<code>NeutrinoPoint</code> PDF is normalized to 2 rather than 1 
to compensate for this.</li> 
</ul> 
 
<p/> 
There is another method, <code>isSetup()</code>, that returns the 
base-class boolean variable <code>isSet</code>. This variable is 
initially <code>true</code>, but could be set <code>false</code> if the 
setup procedure of a PDF failed, e.g. if the user has chosen an unknown 
PDF set. 
 
<p/> 
The MRST/MSTW, CTEQ/CT, NNPDF and H1 PDF routines are based on the 
interpolation in <i>(x, Q)</i> grids. The grid files are stored in the 
<code>xmldoc</code> subdirectory, like settings and particle data. 
Only PDF sets that will be used are read in during the initialization 
stage. Just as input streams can be used to initialize the settings 
and particle data, so can the individual PDFs be constructed.   See 
the header files for explicit constructor descriptions. 
 
</body>
</html>
 
<!-- Copyright (C) 2018 Torbjorn Sjostrand --> 
