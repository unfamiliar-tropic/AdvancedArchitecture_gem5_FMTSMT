/* Author: Sehoon Kim */

#ifndef __FMT__
#define __FMT__

#include "cpu/inst_seq.hh"
#include "debug/FMT.hh"

#define SIZE 50
typedef
struct _FMTentry{
	InstSeqNum instSeq;
	bool mispredBit;
	int branch;
	int L1;
	int L2;
	int tlb;

	//for smt
	int base;
	int wait;

} FMTentry;


class FMT{
	private:
		int size = SIZE;
		FMTentry FMTtable[SIZE];

		/*pointer variables*/
		int dispatch_head;
		int dispatch_tail;
		int fetch;
		
		bool correct_way_fetching;

	public:
		/* functions*/
		FMT();
		void ResetEntry(int i);
		void ResetAll();
	
		void SetCorrectWayFetching(bool b);

		//forwarding pointer functions
		int ForwardFetchPtr(InstSeqNum seq);	
		void ForwardFetchPtr(int i);	
		bool ForwardDispTailPtr();
		void ForwardDispTailPtr(int i);	
		FMTentry *ForwardDispHeadPtr();
		void ForwardDispHeadPtr(int i);

		int FindInst(InstSeqNum seq);

		void BranchUpdate(bool isROBblocked);
		void SetMispredBitOnTail();

		bool NoPendingBranch();
		bool CheckHeadSeq(InstSeqNum seq);
		bool IsInPipeline(int entry);
		bool IsPipelineEmpty();

		//L1, L2, TLB entry update
		void CountL1();
		void CountL2();
		void CountTLB();
		void CountBase();
		void CountWait();

		void CountL1(int n);
		void CountL2(int n);
		void CountTLB(int n);
		void CountBase(int n);
		void CountWait(int n);

		//Debug
		void PrintEntry();
		void DebugPrint();
		void DebugPrint2();
};

#endif
