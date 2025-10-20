// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Student.h"
#include "JsonObjectConverter.h"

UMyGameInstance::UMyGameInstance()
{
}

void UMyGameInstance::Init()
{
	Super::Init();

	//
	// 1. FArchive 를 이용한 일반 C++ 구조체 직렬화
	//

	//  데이터 생성
	FStudentData RawDataSource(1, TEXT("김이박"));

	// 저장 경로
	const FString SavedPath = FPaths::Combine(FPaths::Combine(FPaths::ProjectDir(), TEXT("Saved")));

	UE_LOG(LogTemp, Log, TEXT("저장할 파일 폴더: %s"), *SavedPath);

	/*
	LogTemp: 저장할 파일 폴더: ../../../../../../Workspace/UnrealProjects/UECPP/UEPart1/UnrealSerialization/Saved
	*/
	{
		// 저장할 파일 이름
		const FString RawDataFileName("RawEData.bin");
		FString RawDataAbolutePath = FPaths::Combine(SavedPath, RawDataFileName);

		UE_LOG(LogTemp, Log, TEXT("저장할 파일 전체 경로: %s"), *RawDataFileName);

		/*
		LogTemp: 저장할 파일 전체 경로: RawEData.bin
		*/


		// 경로 조정
		FPaths::MakeStandardFilename(RawDataAbolutePath);
		UE_LOG(LogTemp, Log, TEXT("변경할 파일 폴더: %s"), *RawDataAbolutePath);

		/*
		LogTemp: 변경할 파일 폴더: C:/Workspace/UnrealProjects/UECPP/UEPart1/UnrealSerialization/Saved/RawEData.bin
		*/

		// 파일 저장
		FArchive* RawFileWriter = IFileManager::Get().CreateFileWriter(*RawDataAbolutePath);

		if (RawFileWriter)
		{
			// 직열화
			*RawFileWriter << RawDataSource;
			RawFileWriter->Close();

			delete RawFileWriter;
			RawFileWriter = nullptr;
		}

		// 파일 읽기
		FStudentData RawDataDeserialized;
		FArchive* RawFileReader = IFileManager::Get().CreateFileReader(*RawDataAbolutePath);

		if (RawFileReader)
		{
			// 역직열화
			*RawFileReader << RawDataDeserialized; 
			RawFileReader->Close();
			
			delete RawFileReader;
			RawFileReader = nullptr;

			UE_LOG(LogTemp, Log, TEXT("[RawData] 이름 %s, 순번: %d"), *RawDataDeserialized.Name, RawDataDeserialized.Order);

			/*
			LogTemp: [RawData] 이름 김이박, 순번: 1
			*/
		}
	}

	//
	// 2. FArchive 를 이용한 UObject 직렬화
	//
	/*
	* 바이트 배열(TArray<uint8>)에 데이터를 임시 직렬화 작업을 거친 후
	* 바이트 배열을 파일에 씀
	*/

	// UObject 객체 생성.
	UStudent* StudentSource = NewObject<UStudent>();
	StudentSource->SetName(TEXT("장세윤"));
	StudentSource->SetOrder(13);

	{
		// 파일 저장.
		// 경로 설정.
		const FString ObjectDataFileName(TEXT("ObjectData.bin"));
		FString ObjectDataAbsolutePath = FPaths::Combine(*SavedPath, *ObjectDataFileName);
		FPaths::MakeStandardFilename(ObjectDataAbsolutePath);

		// 파일 저장.
		TUniquePtr<FArchive> FileWriter = 
			TUniquePtr<FArchive>(IFileManager::Get().CreateFileWriter(*ObjectDataAbsolutePath));
			

		// 직렬화

		// 다음 과정을 거침: UObject -> ByteArray -> File 
		TArray<uint8> BufferArray;

		// FMemoryWriter는 전달된 Byte 배열에 데이터 쓰는 기능 제공
		FMemoryWriter MemoryWriter(BufferArray);
		StudentSource->Serialize(MemoryWriter);

		if (FileWriter)
		{
			// [주의] 문제 있는 코드(UObject -> FArchive 불가) ---!
			//*FileWriter << StudentSource;
			
			// 동작하는 코드
			*FileWriter << BufferArray;

			FileWriter->Close();
		}


		// UObject 파일 읽기(역직렬화)

		// File -> ByteArray -> UObject
		TArray<uint8> BufferArrayFromFile;
		TUniquePtr<FArchive> FileReader = TUniquePtr<FArchive>(IFileManager::Get().CreateFileReader(*ObjectDataAbsolutePath));

		if (FileReader)
		{
			*FileReader << BufferArrayFromFile;
			FileReader->Close();
		}

		//  UObject <- ByteArray
		FMemoryReader MemoryReader(BufferArrayFromFile);
		StudentSource->Serialize(MemoryReader);

		// 불러온 데이터 출력
		UE_LOG(LogTemp, Log, TEXT("이름: %s, 순번: %d"), *StudentSource->GetName(), StudentSource->GetOrder())
		/*
		LogTemp: 이름: 장세윤, 순번: 13
		*/
	}

	// Json 직렬화.
	{
		// 직렬화
		// UObject > Json 문자열 > 파일에 저장.
		const FString JsonDataFileName(TEXT("StudentJsonData.txt"));
		// 경로 지정.
		FString JsonDataAbsolutePath
			= FPaths::Combine(*SavedPath, *JsonDataFileName);
		// 경로 정리.
		FPaths::MakeStandardFilename(JsonDataAbsolutePath);

		// UObject > Json 문자열.
		// UObject > JsonObject > JsonWriter > JsonString.

		// 생성할 JsonObject 객체 생성.
		TSharedRef<FJsonObject> JsonObjectSource
			= MakeShared<FJsonObject>();

		// JsonObject에 값 설정.
		FJsonObjectConverter::UStructToJsonObject(
			/*UStudent::StaticClass(),*/
			StudentSource->GetClass(),
			StudentSource,
			JsonObjectSource
		);

		// Json 문자열.
		FString JsonOutString;

		// Json 으로 직렬화 처리를 위한 아카이브 생성.
		auto JsonWriter
			= TJsonWriterFactory<TCHAR>::Create(&JsonOutString);

		// 아카이브를 활용해 Json 문자열 생성.
		if (FJsonSerializer::Serialize(JsonObjectSource, JsonWriter))
		{
			// Json 문자열이 문제 없이 생성되면 파일로 저장.
			if (FFileHelper::SaveStringToFile(
				JsonOutString, *JsonDataAbsolutePath))
			{
				UE_LOG(LogTemp, Log, TEXT("Json 직렬화에 성공했습니다."));
			}
		}

		// 역직렬화.
		// File > JsonString > JsonReader > UObject
		FString JsonInString;
		if (!FFileHelper::LoadFileToString(JsonInString, *JsonDataAbsolutePath))
		{
			UE_LOG(LogTemp, Log, TEXT("Json 데이터 파일 읽기에 실패했습니다."));
			return;
		}

		// JsonReader 생성.
		TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(JsonInString);

		// JsonObject 생성.
		TSharedPtr<FJsonObject> JsonObjectDest;

		// 역직렬화 진행.
		if (FJsonSerializer::Deserialize(JsonReader, JsonObjectDest))
		{
			// 테스트할 UObject.
			UStudent* JsonStudentDest = NewObject<UStudent>();
			if (FJsonObjectConverter::JsonObjectToUStruct(
				JsonObjectDest.ToSharedRef(),
				JsonStudentDest->GetClass(),
				JsonStudentDest
			))
			{
				// 불러온 데이터 출력.
				UE_LOG(
					LogTemp,
					Log,
					TEXT("[JsonData] 이름: %s, 순번: %d"),
					*JsonStudentDest->GetName(),
					JsonStudentDest->GetOrder()
				);
			}
		}

	}
}
