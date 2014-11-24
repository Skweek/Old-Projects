//// Memory Management
//
//#include "Utilities.h" // Declarations
//
//void LogMemory( void* p, char* file, int line )
//{
//
//}
//
//void FreeMemory( void *p )
//{
//
//}
//
//void CleanupMemory()
//{
//
//}
//
//void* New( size_t t, char* File, int Line )
//{
//	void* pAllocation = malloc(t);
//	if( pAllocation )
//	{
//		LogMemory( pAllocation, File, Line );
//	}
//	return pAllocation;
//}
//
//void Delete( void* p )
//{
//	FreeMemory( p );
//}