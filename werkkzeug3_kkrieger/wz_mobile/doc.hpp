// This file is distributed under a BSD license. See LICENSE.txt for details.

#pragma once

#include "_types.hpp"
#include "_types2.hpp"
#include "doc2.hpp"
#include "config.hpp"

class ParaWin_;
class GenMobMesh;

namespace Werkkzeug3Textures {
;

struct GenPara;

class GenType;
class GenVariant;
class GenPrimitive;
class GenClass;
class GenOp;
class GenValue;
class GenPage;
class GenDoc;

/****************************************************************************/
/***                                                                      ***/
/***   Type and op id's                                                   ***/
/***                                                                      ***/
/****************************************************************************/

// all these id's are must not change between versions of the werkkzeug
// so they are explicitly specified
// they only need be unique inside thier enum.

enum GenTypeIds
{
  GTI_UNKNOWN             = 0,
  GTI_BITMAP              = 1,
  GTI_MESH                = 2,
  GTI_MISC                = 3,
};


enum GenClassIds
{
  GCI_UNKNOWN             = 0,
  GCI_NODELOAD            = 0x0001,   // this is a special node generated by optimiser
  GCI_NODESTORE           = 0x0002,   // this is a special node generated by optimiser
  GCI_MISC_COMMENT        = 0x0003, 

  GCI_BITMAP_FLAT         = 0x0101,
  GCI_BITMAP_COLOR        = 0x0103,
  GCI_BITMAP_ADD          = 0x0104,
  GCI_BITMAP_GLOWRECT     = 0x0105,
  GCI_BITMAP_ROTATE       = 0x0106,
  GCI_BITMAP_BLUR         = 0x0107,

  GCI_BITMAP_LOAD         = 0x0108,   // this is an op set by user. it gets removed during optimisation.
  GCI_BITMAP_STORE        = 0x0109,   // this is an op set by user. it gets removed during optimisation.
  GCI_BITMAP_NOP          = 0x010a,   // this is an op set by user. it gets removed during optimisation.

  GCI_BITMAP_NORMALS      = 0x010c,
  GCI_BITMAP_BUMP         = 0x010d,
  GCI_BITMAP_RESIZE       = 0x010f,
  GCI_BITMAP_DEPTH        = 0x0110,

  GCI_BITMAP_PERLIN       = 0x0111,
  GCI_BITMAP_GRADIENT     = 0x0112,
  GCI_BITMAP_CELL         = 0x0113,

  GCI_BITMAP_ROTATEMUL    = 0x0115,
  GCI_BITMAP_DISTORT      = 0x0116,
  GCI_BITMAP_MASK         = 0x0117,
  GCI_BITMAP_COLORRANGE   = 0x0118,
  GCI_BITMAP_COLORBALANCE = 0x0119,
  GCI_BITMAP_CSBOLD       = 0x011a,
  GCI_BITMAP_HSB          = 0x011b,
  GCI_BITMAP_CSB          = 0x011c,
  GCI_BITMAP_TWIRL        = 0x011d,
  GCI_BITMAP_TEXT         = 0x011e,

  GCI_BITMAP_EXPORT       = 0x011f,
  GCI_BITMAP_IMPORT       = 0x0120,


  GCI_MESH_CUBE           = 0x0201,
  GCI_MESH_GRID           = 0x0202,
  GCI_MESH_CYLINDER       = 0x0203,
  GCI_MESH_TORUS          = 0x0204,
  GCI_MESH_SPHERE         = 0x0205,
  GCI_MESH_CAMKEY         = 0x020f,

  GCI_MESH_LOAD           = 0x0208,   // this is an op set by user. it gets removed during optimisation.
  GCI_MESH_STORE          = 0x0209,   // this is an op set by user. it gets removed during optimisation.
  GCI_MESH_NOP            = 0x020a,   // this is an op set by user. it gets removed during optimisation.

  GCI_MESH_MATERIAL       = 0x0211,
  GCI_MESH_ADD            = 0x0212,
  GTI_MESH_SELECTALL      = 0x0213,
  GCI_MESH_SELECTCUBE     = 0x0214,
  GCI_MESH_DELETEFACES    = 0x0215,
  GCI_MESH_INVERT         = 0x0216,

  GCI_MESH_TRANSFORMEX    = 0x0221,
  GCI_MESH_DISPLACE       = 0x0222,
  GCI_MESH_PERLIN         = 0x0223,
  GCI_MESH_EXTRUDENORMAL  = 0x0224,
  GCI_MESH_BEND2          = 0x0225,
  GCI_MESH_TRANSFORM      = 0x0227,
  GCI_MESH_MULTIPLY       = 0x0228,
  GCI_MESH_LIGHT          = 0x0229,
  GCI_MESH_LIGHTMIX       = 0x022a,
  GCI_MESH_BEND           = 0x022b,
};

/****************************************************************************/
/***                                                                      ***/
/***   structs                                                            ***/
/***                                                                      ***/
/****************************************************************************/

typedef sString<32> GenName;

enum GenParaType
{
  GPT_OFF = 0,
  GPT_LABEL,
  GPT_CHOICE,
  GPT_FLAGS,
  GPT_INT,
  GPT_FLOAT,
  GPT_COLOR,
  GPT_STRING,
  GPT_LINK,
  GPT_CONTRAST,
  GPT_FILENAME,
  GPT_TEXT,
};

enum GenParaFlags
{
  GPF_WIDER1                      = 0x0001, // make control 1 slot wider
  GPF_WIDER2                      = 0x0002, // make control 2 slots wider
  GPF_WIDER3                      = 0x0003, // make control 3 slots wider
  GPF_FULLWIDTH                   = 0x0004, // extend control to full width
  GPF_LABEL                       = 0x0008, // start new line and print label
  GPF_LINK_REQUIRED               = 0x0010,
  GPF_INVISIBLE                   = 0x0020, // hide old or internal parameters
  GPF_DEFAULT                     = GPF_FULLWIDTH|GPF_LABEL,
};

struct GenPara                              // a parameter 
{
  const sChar *Name;                        // user-interface name of parameter
  const sChar *Choices;                     // cycle-option string (if GPT_CYCLE)
  sU32 ParaId;                              // unique identifier, used to find parameter

  sInt Type;                                // GPT_???
  sInt Flags;                               // GPF_???
  sInt Count;                               // INT, FLOAT, STRING, LINK
  class GenType *OutputType;                // LINK

  sF32 Min[4];                              // gui control
  sF32 Max[4];
  sF32 Default[4];
  sF32 Step;

  sF32 Offset,Scale;                        // real_para = edit_para * Scale + Offset

  void Init();
  static GenPara MakeLabel(const sChar *name);
  static GenPara MakeChoice(sInt id,const sChar *name,const sChar *choices,sInt def=0,sInt flags=GPF_DEFAULT);
  static GenPara MakeFlags(sInt id,const sChar *name,const sChar *choices,sInt def=0,sInt flags=GPF_DEFAULT);
  static GenPara MakeInt(sInt id,const sChar *name,sInt max=256,sInt min=0,sInt def=0,sF32 step=0.25f,sInt flags=GPF_DEFAULT);
  static GenPara MakeFloat(sInt id,const sChar *name,sInt max=256,sInt min=0,sInt def=0,sF32 step=0.25f,sInt flags=GPF_DEFAULT);
  static GenPara MakeIntV(sInt id,const sChar *name,sInt count,sInt max=256,sInt min=0,sInt def=0,sF32 step=0.25f,sInt flags=GPF_DEFAULT);
  static GenPara MakeFloatV(sInt id,const sChar *name,sInt count,sInt max=256,sInt min=0,sF32 def=0,sF32 step=0.25f,sInt flags=GPF_DEFAULT);
  static GenPara MakeColor(sInt id,const sChar *name,sU32 def=0xff000000,sInt flags=GPF_DEFAULT);
  static GenPara MakeString(sInt id,const sChar *name,sInt size=32,const sChar *def=0,sInt flags=GPF_DEFAULT);
  static GenPara MakeLink(sInt id,const sChar *name,class GenType *type,sInt flags=GPF_DEFAULT);
  static GenPara MakeContrast(sInt id,const sChar *name="Contrast",sInt flags=GPF_DEFAULT);
  static GenPara MakeFilename(sInt id,const sChar *name="",const sChar *def=0,sInt flags=GPF_DEFAULT);
  static GenPara MakeText(sInt id,const sChar *name,const sChar *def=0,sInt flags=GPF_DEFAULT);

  class GenValue *Value;                    // backlink to value, only temporary set while MakeNode
};

enum GenInputFlags
{
  GIF_REQUIRED      = 0x0001,               // if not connected, error
  GIF_MULTIPLE      = 0x0002,               // can be repeated (only for last input, for add-like ops)
  GIF_DONTFOLLOW    = 0x0004,               // don't really follow node, just store op / cache
};

struct GenInput                             // an input or link
{
  const sChar *Name;                        // name (only for links)
  sInt ParaId;                              // unique id
  GenType *Type;                            // type of input
  sInt Flags;                               // GIF_???
  static GenInput Make(sInt Id,GenType *Type,const sChar *Name=0,sInt Flags=0);
};

/****************************************************************************/
/***                                                                      ***/
/***   classes                                                            ***/
/***                                                                      ***/
/****************************************************************************/

class GenType                               // a type, like BITMAP or MESH
{
public:
  GenName Name;
  sU32 Color;
  sInt TypeId;
  sAutoArray<class GenVariant> Variants;

  void AddVariant(const sChar *Name,sInt VariantId);
};

class GenVariant                            // a variant, like 8BIT GREY or 16BIT RGBA
{
public:
  GenName Name;
  sInt VariantId;
  GenType *Type;
};
/*
class GenPrimitive                          // an actual operator, real code!
{
public:
  GenName Name;                             // multiple primitives can have same name and different type-variant
  GenVariant *Output;
  sArray2<GenVariant *> Inputs;
  sArray2<GenPara> Para;

  sInt Flags;                               // type specific flags
  void *Handler;                            // type specific code ptr
};
*/
class GenClass                              // map operator parameters to real parameters
{
public:
  GenName Name;                             // user-interface Name
  sInt Version;                             // version of this macro
  sInt ClassId;                             // unique id 
  sInt Flags;                               // GCF_???
  sInt Column;                              // for palette
  sInt Shortcut;                            // keyboard shortcut
  GenType *Output;                          // output type. variant depends on input

  sMap<GenHandler,sInt> Handlers;           // code that does the work...
  sArray2<GenInput> Inputs;                 // inputs
  sArray2<GenPara> Para;                    // parameter

  sInt NextParaId;                          // next id when a new parameter gets added

  GenClass();
  virtual ~GenClass();
  virtual GenNode *MakeNode(GenOp *op,sInt variantid,sInt sx,sInt sy);
  virtual void DrawHints(GenOp *op,sInt handle);
};

enum GenClassFlags
{
  GCF_NOP       = 0x0001,                   // nop class op: pass input to output and remove node!
  GCF_LOAD      = 0x0002,                   // load class op: pass link to output and remove node!
  GCF_STORE     = 0x0004,                   // store class op: only for optics.
  GCF_COMMENT   = 0x0008,                   // comment ops have many specialities..
};

enum GenClassColumns                        // sort ops in op-palette
{
  GCC_GENERATOR = 0,                        // no inputs
  GCC_FILTER    = 1,                        // one input / one output
  GCC_ADD       = 2,                        // merge multiple inputs
  GCC_LINK      = 2,                        // load / store / nop
  GCC_SPECIAL   = 2,                        // something else
  GCC_MAX       = 3,                        // max # of columns
  GCC_INVISIBLE = -1,                       // do not list
};


/****************************************************************************/

class GenValue                              // one parameter's value
{
public:
  GenValue();
  virtual ~GenValue();

  virtual GenValue *Copy()=0;                         // create a clone
  virtual void Default(GenPara *)=0;                  // initialize new value (based on default parameters)
  virtual void Read(GenPara *,sU32 *&data)=0;         // read value
  virtual void Write(sU32 *&data)=0;                  // write value
  virtual void MakeGui(sGridFrame *,sInt x0,sInt x1,sInt y,ParaWin_ *parawin)=0; // add gui elements in grid
  virtual sInt GetParaSize()=0;                       // get size of parameter in node
  virtual void StorePara(GenOp *op,sInt *d)=0;        // store parameter in node

  GenPara *Para;                                      // The parameter associated to this value. may be 0 when versions don't match
  sInt ParaId;                                        // parameter id, in case (*Para==0)
};

GenValue *CreateValue(GenPara *gp);         // create value class depending on gp->Type. does not call Default()

/****************************************************************************/

class GenOp : public sObject
{
  void GenOp::CombinedConstructor();
public:
  GenOp();
  GenOp(sInt x,sInt y,sInt w,GenClass *cl,const sChar *n);
  ~GenOp();
  void Tag();
  void Copy(GenOp *);
  void FlushCache();
  struct Link_
  {
    class GenValueLink *Name;
    GenOp *Link;
    GenNode *Node;
    Link_() { Link=0; Name=0; }
  };

  void Create();                            // this is a new op, not one read from file
//  sBool Read(sU32 *&);
//  sBool Write(sU32 *&);

  GenValue *FindValue(sInt ParaId);
  const GenValue *FindValue(sInt ParaId) const;
  GenObject *FindVariant(sInt var);

  sInt PosX;
  sInt PosY;
  sInt Width;
  sInt Height;
  sInt Selected;
  GenName StoreName;
  GenClass *Class;

  sInt Bypass;
  sInt Hide;
  sInt Error;
  sInt ExportRoot;                          // this is one of the export-roots. flag is set during export process

  sList<GenOp> *Inputs;
  sList<GenOp> *Outputs;
  sArray2<Link_> Links;
  sArray2<GenNode *> Nodes;
  sAutoArray<GenValue> Values;

  sAutoArray<GenObject> Cache;
  sInt CacheVariant;
  GenMobMesh *CacheMesh;
  sBool Changed;

  sInt CalcCount;

  sBool CanChangeHeight() { return Class->Flags & GCF_COMMENT; }
};

GenOp *FollowOp(GenOp *op);

class GenPage : public sObject
{
public:
  GenPage(const sChar *n);
  void Tag();
  ~GenPage();

  GenName Name;
  sObjList<GenOp> Ops;
  sList<GenOp> *Stores;
  
  void Connect1();                          // find stores
  sBool Connect2();                          // connect ops (return true if changed)
  GenOp *FindOp(const sChar *name);
};

class GenDoc : public sObject
{
  sU8 *NodeHeap;
  sInt NodeHeapAlloc;
  sInt NodeHeapUsed;
public:
  GenDoc();
  ~GenDoc();
  void Clear();                             // clear USER part of the doc, not classes and stuff
  void Tag();
  sBool Write(sU32 *&data);
  sBool Read(sU32 *&data);
  sBool Export(sU32 *&data,GenOp *op);
  sBool Load(const sChar *name);
  sBool Save(const sChar *name);

  sList<GenPage> *Pages;
  sAutoArray<GenClass> Classes;
  sAutoArray<GenType> Types;

  GenType *FindType(sInt gti);
  GenClass *FindClass(sInt gci);
  GenOp *FindOp(const sChar *name);
  GenPage *FindPage(GenOp *op);
  void RenameOps(const sChar *oldname,const sChar *newname);

  sU8 *AllocNode(sInt bytes);
  template <class Type> Type *AllocNode() { return (Type *)AllocNode(sizeof(Type)); }
  template <class Type> Type *AllocNode(sInt n) { return (Type *)AllocNode(sizeof(Type)*n); }
  void Connect();
  void ChangeR(GenOp *op);
  void Change();
  void MakeNodePrepare();
  GenNode *MakeNodeTree(GenOp *op,sInt variantid,sInt sx,sInt sy);
  GenNode *MakeNodeR(GenOp *op,sInt variantid,sInt sx,sInt sy);
  GenNode *OptimiseNode1R(GenNode *node);
  void OptimiseNode2R(GenNode *node);
  void OptimiseNode3R(GenNode *node,GenNode **patch);
  void OptimiseNode4R(GenNode *node,sInt &count);
  void WriteNode(GenNode *node,sU32 *&data);
  void FlushCache();

  sInt ExportBitmaps();
};

extern GenDoc *Doc;

/****************************************************************************/
/****************************************************************************/

class GenValueInt : public GenValue                   // CYLCE, FLAGS
{
public:
  sInt Value;

  GenValue *Copy();
  void Default(GenPara *);
  void Read(GenPara *,sU32 *&data);
  void Write(sU32 *&data);
  void MakeGui(sGridFrame *,sInt x0,sInt x1,sInt y,ParaWin_ *parawin);
  sInt GetParaSize() { return 1; }
  void StorePara(GenOp *op,sInt *d);
};

class GenValueIntV : public GenValue        // INT
{
public:
  sInt Values[4];

  GenValue *Copy();
  void Default(GenPara *);
  void Read(GenPara *,sU32 *&data);
  void Write(sU32 *&data);
  void MakeGui(sGridFrame *,sInt x0,sInt x1,sInt y,ParaWin_ *parawin);
  sInt GetParaSize() { return Para->Count; }
  void StorePara(GenOp *op,sInt *d);
};

class GenValueFloatV : public GenValue      // FLOAT
{
public:
  sF32 Values[4];

  GenValue *Copy();
  void Default(GenPara *);
  void Read(GenPara *,sU32 *&data);
  void Write(sU32 *&data);
  void MakeGui(sGridFrame *,sInt x0,sInt x1,sInt y,ParaWin_ *parawin);
  sInt GetParaSize() { return Para->Count; }
  void StorePara(GenOp *op,sInt *d);
};

class GenValueColor : public GenValue      // RGBA Color
{
public:
  sF32 Values[4];

  GenValue *Copy();
  void Default(GenPara *);
  void Read(GenPara *,sU32 *&data);
  void Write(sU32 *&data);
  void MakeGui(sGridFrame *,sInt x0,sInt x1,sInt y,ParaWin_ *parawin);
  sInt GetParaSize() { return 1; }
  void StorePara(GenOp *op,sInt *d);
};

class GenValueString : public GenValue      // STRING
{
public:
  GenValueString();
  ~GenValueString();
  sInt Size;
  sChar *Buffer;

  GenValue *Copy();
  void Default(GenPara *);
  void Read(GenPara *,sU32 *&data);
  void Write(sU32 *&data);
  void MakeGui(sGridFrame *,sInt x0,sInt x1,sInt y,ParaWin_ *parawin);
  sInt GetParaSize();
  void StorePara(GenOp *op,sInt *d);
};

class GenValueText : public GenValue      // STRING
{
public:
  GenValueText();
  ~GenValueText();
  class sText *Text;

  GenValue *Copy();
  void Default(GenPara *);
  void Read(GenPara *,sU32 *&data);
  void Write(sU32 *&data);
  void MakeGui(sGridFrame *,sInt x0,sInt x1,sInt y,ParaWin_ *parawin);
  sInt GetParaSize();
  void StorePara(GenOp *op,sInt *d);
};

class GenValueFilename : public GenValueString
{
public:
  GenValue *Copy();
  void MakeGui(sGridFrame *,sInt x0,sInt x1,sInt y,ParaWin_ *parawin);
};

class GenValueLink : public GenValueString  // LINK
{
public:
  GenValue *Copy();
  sInt GetParaSize() { return 0; }
  void StorePara(GenOp *op,sInt *d) {} // { *d++ = (sInt)(op->Links[0].Node); }
  void MakeGui(sGridFrame *,sInt x0,sInt x1,sInt y,ParaWin_ *parawin);
};

class GenValueContrast : public GenValue      // FLOAT
{
public:
  sF32 Values[4];

  GenValue *Copy();
  void Default(GenPara *);
  void Read(GenPara *,sU32 *&data);
  void Write(sU32 *&data);
  void MakeGui(sGridFrame *,sInt x0,sInt x1,sInt y,ParaWin_ *parawin);
  sInt GetParaSize() { return Para->Count; }
  void StorePara(GenOp *op,sInt *d);
};

/****************************************************************************/
/****************************************************************************/

}; // namespace Werkkzeug3Textures
using namespace Werkkzeug3Textures;