/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                                           */
/*                  This file is part of the program and library             */
/*         SCIP --- Solving Constraint Integer Programs                      */
/*                                                                           */
/*    Copyright (C) 2002-2016 Konrad-Zuse-Zentrum                            */
/*                            fuer Informationstechnik Berlin                */
/*                                                                           */
/*  SCIP is distributed under the terms of the ZIB Academic License.         */
/*                                                                           */
/*  You should have received a copy of the ZIB Academic License              */
/*  along with SCIP; see the file COPYING. If not email to scip@zib.de.      */
/*                                                                           */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/**@file   type_event.h
 * @ingroup TYPEDEFINITIONS
 * @brief  type definitions for managing events
 * @author Tobias Achterberg
 *
 *  This file defines the interface for event handler implemented in C.
 *
 *  - \ref scip::ObjEventhdlr "C++ wrapper class"
 */

/*---+----1----+----2----+----3----+----4----+----5----+----6----+----7----+----8----+----9----+----0----+----1----+----2*/

#ifndef __SCIP_TYPE_EVENT_H__
#define __SCIP_TYPE_EVENT_H__

#include "scip/def.h"
#include "scip/type_retcode.h"
#include "scip/type_scip.h"

#ifdef __cplusplus
extern "C" {
#endif

/*
 * event types
 */

#define SCIP_EVENTTYPE_DISABLED       0x00000000u /**< the event was disabled and has no effect any longer */

/* variable events */
#define SCIP_EVENTTYPE_VARADDED       0x00000001u /**< a variable has been added to the transformed problem */
#define SCIP_EVENTTYPE_VARDELETED     0x00000002u /**< a variable will be deleted from the transformed problem */
#define SCIP_EVENTTYPE_VARFIXED       0x00000004u /**< a variable has been fixed, aggregated, or multi-aggregated */
#define SCIP_EVENTTYPE_VARUNLOCKED    0x00000008u /**< the number of rounding locks of a variable was reduced to zero or
                                                   *   one */
#define SCIP_EVENTTYPE_OBJCHANGED     0x00000010u /**< the objective value of a variable has been changed */
#define SCIP_EVENTTYPE_GLBCHANGED     0x00000020u /**< the global lower bound of a variable has been changed */
#define SCIP_EVENTTYPE_GUBCHANGED     0x00000040u /**< the global upper bound of a variable has been changed */
#define SCIP_EVENTTYPE_LBTIGHTENED    0x00000080u /**< the local lower bound of a variable has been increased */
#define SCIP_EVENTTYPE_LBRELAXED      0x00000100u /**< the local lower bound of a variable has been decreased */
#define SCIP_EVENTTYPE_UBTIGHTENED    0x00000200u /**< the local upper bound of a variable has been decreased */
#define SCIP_EVENTTYPE_UBRELAXED      0x00000400u /**< the local upper bound of a variable has been increased */
#define SCIP_EVENTTYPE_GHOLEADDED     0x00000800u /**< a global hole has been added to the hole list of a variable's domain */
#define SCIP_EVENTTYPE_GHOLEREMOVED   0x00001000u /**< a global hole has been removed from the hole list of a variable's domain */
#define SCIP_EVENTTYPE_LHOLEADDED     0x00002000u /**< a local hole has been added to the hole list of a variable's domain */
#define SCIP_EVENTTYPE_LHOLEREMOVED   0x00004000u /**< a local hole has been removed from the hole list of a variable's domain */
#define SCIP_EVENTTYPE_IMPLADDED      0x00008000u /**< the variable's implication list, variable bound or clique information
                                                   *   was extended */

/* presolving events */
#define SCIP_EVENTTYPE_PRESOLVEROUND  0x00010000u /**< a presolving round has been finished */

/* node events */
#define SCIP_EVENTTYPE_NODEFOCUSED    0x00020000u /**< a node has been focused and is now the focus node */
#define SCIP_EVENTTYPE_NODEFEASIBLE   0x00040000u /**< the LP/pseudo solution of the node was feasible */
#define SCIP_EVENTTYPE_NODEINFEASIBLE 0x00080000u /**< the focus node has been proven to be infeasible or was bounded */
#define SCIP_EVENTTYPE_NODEBRANCHED   0x00100000u /**< the focus node has been solved by branching */

/* LP events */
#define SCIP_EVENTTYPE_FIRSTLPSOLVED  0x00200000u /**< the node's initial LP was solved */
#define SCIP_EVENTTYPE_LPSOLVED       0x00400000u /**< the node's LP was completely solved with cut & price */

/* primal solution events */
#define SCIP_EVENTTYPE_POORSOLFOUND   0x00800000u /**< a good enough primal feasible (but not new best) solution was found */
#define SCIP_EVENTTYPE_BESTSOLFOUND   0x01000000u /**< a new best primal feasible solution was found */

/* linear row events */
#define SCIP_EVENTTYPE_ROWADDEDSEPA   0x02000000u /**< a row has been added to SCIP's separation storage */
#define SCIP_EVENTTYPE_ROWDELETEDSEPA 0x04000000u /**< a row has been removed from SCIP's separation storage */
#define SCIP_EVENTTYPE_ROWADDEDLP     0x08000000u /**< a row has been added to the LP */
#define SCIP_EVENTTYPE_ROWDELETEDLP   0x10000000u /**< a row has been removed from the LP */
#define SCIP_EVENTTYPE_ROWCOEFCHANGED 0x20000000u /**< a coefficient of a row has been changed (row specific event) */
#define SCIP_EVENTTYPE_ROWCONSTCHANGED 0x40000000u/**< the constant of a row has been changed (row specific event) */
#define SCIP_EVENTTYPE_ROWSIDECHANGED 0x80000000u /**< a side of a row has been changed (row specific event) */

/* event masks for variable events */
#define SCIP_EVENTTYPE_GBDCHANGED     (SCIP_EVENTTYPE_GLBCHANGED | SCIP_EVENTTYPE_GUBCHANGED)
#define SCIP_EVENTTYPE_LBCHANGED      (SCIP_EVENTTYPE_LBTIGHTENED | SCIP_EVENTTYPE_LBRELAXED)
#define SCIP_EVENTTYPE_UBCHANGED      (SCIP_EVENTTYPE_UBTIGHTENED | SCIP_EVENTTYPE_UBRELAXED)
#define SCIP_EVENTTYPE_BOUNDTIGHTENED (SCIP_EVENTTYPE_LBTIGHTENED | SCIP_EVENTTYPE_UBTIGHTENED)
#define SCIP_EVENTTYPE_BOUNDRELAXED   (SCIP_EVENTTYPE_LBRELAXED | SCIP_EVENTTYPE_UBRELAXED)
#define SCIP_EVENTTYPE_BOUNDCHANGED   (SCIP_EVENTTYPE_LBCHANGED | SCIP_EVENTTYPE_UBCHANGED)
#define SCIP_EVENTTYPE_GHOLECHANGED   (SCIP_EVENTTYPE_GHOLEADDED | SCIP_EVENTTYPE_GHOLEREMOVED)
#define SCIP_EVENTTYPE_LHOLECHANGED   (SCIP_EVENTTYPE_LHOLEADDED | SCIP_EVENTTYPE_LHOLEREMOVED)
#define SCIP_EVENTTYPE_HOLECHANGED    (SCIP_EVENTTYPE_GHOLECHANGED | SCIP_EVENTTYPE_LHOLECHANGED)
#define SCIP_EVENTTYPE_DOMCHANGED     (SCIP_EVENTTYPE_BOUNDCHANGED | SCIP_EVENTTYPE_HOLECHANGED)
#define SCIP_EVENTTYPE_VARCHANGED     (SCIP_EVENTTYPE_VARFIXED | SCIP_EVENTTYPE_VARUNLOCKED | SCIP_EVENTTYPE_OBJCHANGED \
                                       | SCIP_EVENTTYPE_GBDCHANGED | SCIP_EVENTTYPE_DOMCHANGED | SCIP_EVENTTYPE_IMPLADDED \
                                       | SCIP_EVENTTYPE_VARDELETED)
#define SCIP_EVENTTYPE_VAREVENT       (SCIP_EVENTTYPE_VARADDED | SCIP_EVENTTYPE_VARCHANGED)

/* event masks for node events */
#define SCIP_EVENTTYPE_NODESOLVED     (SCIP_EVENTTYPE_NODEFEASIBLE | SCIP_EVENTTYPE_NODEINFEASIBLE \
                                       | SCIP_EVENTTYPE_NODEBRANCHED)
#define SCIP_EVENTTYPE_NODEEVENT      (SCIP_EVENTTYPE_NODEFOCUSED | SCIP_EVENTTYPE_NODESOLVED)

/* event masks for LP events */
#define SCIP_EVENTTYPE_LPEVENT        (SCIP_EVENTTYPE_FIRSTLPSOLVED | SCIP_EVENTTYPE_LPSOLVED)

/* event masks for primal solution events */
#define SCIP_EVENTTYPE_SOLFOUND       (SCIP_EVENTTYPE_POORSOLFOUND | SCIP_EVENTTYPE_BESTSOLFOUND)
#define SCIP_EVENTTYPE_SOLEVENT       (SCIP_EVENTTYPE_SOLFOUND)

/* event masks for row events */
#define SCIP_EVENTTYPE_ROWCHANGED     (SCIP_EVENTTYPE_ROWCOEFCHANGED | SCIP_EVENTTYPE_ROWCONSTCHANGED | SCIP_EVENTTYPE_ROWSIDECHANGED)
#define SCIP_EVENTTYPE_ROWEVENT       (SCIP_EVENTTYPE_ROWADDEDSEPA | SCIP_EVENTTYPE_ROWDELETEDSEPA | SCIP_EVENTTYPE_ROWADDEDLP | SCIP_EVENTTYPE_ROWDELETEDLP | SCIP_EVENTTYPE_ROWCHANGED)

typedef unsigned int SCIP_EVENTTYPE;         /**< type of event (bit field) */


typedef struct SCIP_Eventhdlr SCIP_EVENTHDLR;     /**< event handler for a specific events */
typedef struct SCIP_EventhdlrData SCIP_EVENTHDLRDATA; /**< event handler data */
typedef struct SCIP_Event SCIP_EVENT;             /**< event data structure */
typedef struct SCIP_EventVarAdded SCIP_EVENTVARADDED; /**< data for variable addition events */
typedef struct SCIP_EventVarDeleted SCIP_EVENTVARDELETED; /**< data for variable deletion events */
typedef struct SCIP_EventVarFixed SCIP_EVENTVARFIXED; /**< data for variable fixing events */
typedef struct SCIP_EventVarUnlocked SCIP_EVENTVARUNLOCKED; /**< data for variable unlocked events */
typedef struct SCIP_EventObjChg SCIP_EVENTOBJCHG; /**< data for objective value change events */
typedef struct SCIP_EventBdChg SCIP_EVENTBDCHG;   /**< data for bound change events */
typedef struct SCIP_EventHole SCIP_EVENTHOLE;     /**< data for domain hole events */
typedef struct SCIP_EventImplAdd SCIP_EVENTIMPLADD; /**< data for implication added events */
typedef struct SCIP_EventRowAddedSepa SCIP_EVENTROWADDEDSEPA; /**< data for row addition to sepastorage events */
typedef struct SCIP_EventRowDeletedSepa SCIP_EVENTROWDELETEDSEPA; /**< data for row deletion from sepastorage events */
typedef struct SCIP_EventRowAddedLP SCIP_EVENTROWADDEDLP; /**< data for row addition to LP events */
typedef struct SCIP_EventRowDeletedLP SCIP_EVENTROWDELETEDLP; /**< data for row deletion from LP events */
typedef struct SCIP_EventRowCoefChanged SCIP_EVENTROWCOEFCHANGED; /**< data for row coefficient change events */
typedef struct SCIP_EventRowConstChanged SCIP_EVENTROWCONSTCHANGED; /**< data for row constant change events */
typedef struct SCIP_EventRowSideChanged SCIP_EVENTROWSIDECHANGED; /**< data for row side change events */
typedef struct SCIP_EventData SCIP_EVENTDATA;     /**< locally defined event specific data */
typedef struct SCIP_EventFilter SCIP_EVENTFILTER; /**< event filter to select events to be processed by an event handler */
typedef struct SCIP_EventQueue SCIP_EVENTQUEUE;   /**< event queue to cache events and process them later */

/** copy method for event handler plugins (called when SCIP copies plugins)
 *
 *  input:
 *  - scip            : SCIP main data structure
 *  - eventhdlr       : the event handler itself
 */
#define SCIP_DECL_EVENTCOPY(x) SCIP_RETCODE x (SCIP* scip, SCIP_EVENTHDLR* eventhdlr)

/** destructor of event handler to free user data (called when SCIP is exiting)
 *
 *  input:
 *  - scip            : SCIP main data structure
 *  - eventhdlr       : the event handler itself
 */
#define SCIP_DECL_EVENTFREE(x) SCIP_RETCODE x (SCIP* scip, SCIP_EVENTHDLR* eventhdlr)

/** initialization method of event handler (called after problem was transformed)
 *
 *  input:
 *  - scip            : SCIP main data structure
 *  - eventhdlr       : the event handler itself
 */
#define SCIP_DECL_EVENTINIT(x) SCIP_RETCODE x (SCIP* scip, SCIP_EVENTHDLR* eventhdlr)

/** deinitialization method of event handler (called before transformed problem is freed)
 *
 *  input:
 *  - scip            : SCIP main data structure
 *  - eventhdlr       : the event handler itself
 */
#define SCIP_DECL_EVENTEXIT(x) SCIP_RETCODE x (SCIP* scip, SCIP_EVENTHDLR* eventhdlr)

/** solving process initialization method of event handler (called when branch and bound process is about to begin)
 *
 *  This method is called when the presolving was finished and the branch and bound process is about to begin.
 *  The event handler may use this call to initialize its branch and bound specific data.
 *
 *  input:
 *  - scip            : SCIP main data structure
 *  - eventhdlr       : the event handler itself
 */
#define SCIP_DECL_EVENTINITSOL(x) SCIP_RETCODE x (SCIP* scip, SCIP_EVENTHDLR* eventhdlr)

/** solving process deinitialization method of event handler (called before branch and bound process data is freed)
 *
 *  This method is called before the branch and bound process is freed.
 *  The event handler should use this call to clean up its branch and bound data.
 *
 *  input:
 *  - scip            : SCIP main data structure
 *  - eventhdlr       : the event handler itself
 */
#define SCIP_DECL_EVENTEXITSOL(x) SCIP_RETCODE x (SCIP* scip, SCIP_EVENTHDLR* eventhdlr)

/** frees specific event data
 *
 *  input:
 *  - scip            : SCIP main data structure
 *  - eventhdlr       : the event handler itself
 *  - eventdata       : pointer to the event data to free
 */
#define SCIP_DECL_EVENTDELETE(x) SCIP_RETCODE x (SCIP* scip, SCIP_EVENTHDLR* eventhdlr, SCIP_EVENTDATA** eventdata)

/** execution method of event handler
 *
 *  Processes the event. The method is called every time an event occurs, for which the event handler
 *  is responsible. Event handlers may declare themselves responsible for events by calling the
 *  corresponding SCIPcatch...() method. This method creates an event filter object to point to the
 *  given event handler and event data.
 *
 *  input:
 *  - scip            : SCIP main data structure
 *  - eventhdlr       : the event handler itself
 *  - event           : event to process
 *  - eventdata       : user data for the event
 */
#define SCIP_DECL_EVENTEXEC(x) SCIP_RETCODE x (SCIP* scip, SCIP_EVENTHDLR* eventhdlr, SCIP_EVENT* event, SCIP_EVENTDATA* eventdata)

#ifdef __cplusplus
}
#endif

#endif
