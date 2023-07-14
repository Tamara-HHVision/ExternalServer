#pragma once
#include "cim_pch.h"
#include "pfr/core.hpp"
#include "NetworkUtilities/NetworkPacketUtils.h"

namespace CIM_Backend 
{
	class NetworkPacketUtils
	{
	private:

		NetworkPacketUtils() {}

	public:
		/// <summary>
		/// Writes data from header and then from data struct into a specifed buffer
		/// </summary>
		/// <typeparam name="T">Data Struct Type</typeparam>
		/// <typeparam name="U">Header Struct Type</typeparam>
		/// <param name="header">header reference</param>
		/// <param name="data">data reference</param>
		/// <param name="buf">buffer reference</param>
		template <typename T, typename U>
		static void SerializePacket(U& header, T& data, char* buf)
		{
			int offset = 0;
			SerializePacket(header, buf, &offset);
			SerializePacket(data, buf, &offset);
		}


		/// <summary>
		/// Writes data from header and then from data struct into a specified buffer with specified offset
		/// </summary>
		/// <typeparam name="T">Data Struct Type</typeparam>
		/// <typeparam name="U">Header Struct Type</typeparam>
		/// <param name="header">header reference</param>
		/// <param name="data">data reference</param>
		/// <param name="buf">buffer reference</param>
		/// <param name="writeOffset">reference to offset to start writing</param>
		template <typename T, typename U>
		static void SerializePacket(U& header, T& data, char* buf, int* writeOffset)
		{
			SerializePacket(header, buf, writeOffset);
			SerializePacket(data, buf, writeOffset);
		}


		/// <summary>
		///  Writes data from data struct into a specified buffer
		/// </summary>
		/// <typeparam name="T">Data Struct Type</typeparam>
		/// <param name="data">data reference</param>
		/// <param name="buf">buffer reference</param>
		template <typename T>
		static void SerializePacket(T& data, char* buf)
		{
			int offset = 0;
			pfr::for_each_field(data, [&](const auto& member)
			{
				using memberDREF = decltype(std::remove_reference_t<decltype(member)>());
				{
					if constexpr (!std::is_compound<memberDREF>())
					{
						WriteSimpleData(buf, member, &offset);
						Log::LogInfoToFile("Data {}", member);
					}
					else
					{
						SerializePacket(member, buf, &offset);
					}
				}
			});
		}


		/// <summary>
		///  Writes data from data struct into a specified buffer with specified offset
		/// </summary>
		/// <typeparam name="T">Data Struct Type</typeparam>
		/// <param name="data">data reference</param>
		/// <param name="buf">buffer reference</param>
		/// <param name="writeOffset">reference to offset to start writing</param>
		template <typename T>
		static void SerializePacket(T& data, char* buf, int* writeOffset)
		{
			pfr::for_each_field(data, [&](const auto& member)
			{
				using memberDREF = decltype(std::remove_reference_t<decltype(member)>());
				{
					if constexpr (!std::is_compound<memberDREF>())
					{
						WriteSimpleData(buf, member, writeOffset);
					}
					else
					{
						SerializePacket(member, buf, writeOffset);
					}
				}
			});
		}


		/// <summary>
		/// Writes data from header and then from data struct into a specified buffer
		/// </summary>
		/// <typeparam name="T">Data Struct Type</typeparam>
		/// <typeparam name="U">Header Struct Type</typeparam>
		/// <param name="header">header reference</param>
		/// <param name="data">data reference</param>
		/// <param name="buf">buffer reference</param>
		template <typename T, typename U>
		static void DeserializePacket(U& header, T& data, char* buf)
		{
			int offset = 0;
			DeserializePacket(header, buf, &offset);
			DeserializePacket(data, buf, &offset);
		}


		/// <summary>
		/// Reads data from buffer into header and then into data struct with specified offset
		/// </summary>
		/// <typeparam name="T">Data Struct Type</typeparam>
		/// <typeparam name="U">Header Struct Type</typeparam>
		/// <param name="header">header reference</param>
		/// <param name="data">data reference</param>
		/// <param name="buf">buffer reference</param>
		/// <param name="writeOffset">reference to offset with which to start reading</param>
		template <typename T, typename U>
		static void DeserializePacket(U& header, T& data, char* buf, int* writeOffset)
		{
			DeserializePacket(header, buf, writeOffset);
			DeserializePacket(data, buf, writeOffset);
		}


		/// <summary>
		/// Reads data from buffer into data struct
		/// </summary>
		/// <typeparam name="T">Data Struct Type</typeparam>
		/// <param name="data">Data reference</param>
		/// <param name="buf">buffer reference</param>
		template <typename T>
		static void DeserializePacket(T& data, char* buf)
		{
			int offset = 0;
			pfr::for_each_field(data, [&](auto& member)
			{
				using memberDREF = decltype(std::remove_reference_t<decltype(member)>());
				{
					if constexpr (!std::is_compound<memberDREF>())
					{
						member = ReadSimpleData<memberDREF>(buf, &offset);
					}
					else
					{
						DeserializePacket(member, buf, &offset);
					}
				}
			});
		}


		/// <summary>
		/// Reads data from buffer into data struct with specified offset
		/// </summary>
		/// <typeparam name="T">Data Struct Type</typeparam>
		/// <param name="data">Data reference</param>
		/// <param name="buf">buffer reference</param>
		/// <param name="readOffset">reference to offset with which to start reading</param>
		template <typename T>
		static void DeserializePacket(T& data, char* buf, int* readOffset)
		{
			pfr::for_each_field(data, [&](auto& member)
			{
				using memberDREF = decltype(std::remove_reference_t<decltype(member)>());
				{
					if constexpr (!std::is_compound<memberDREF>())
					{
						member = ReadSimpleData<memberDREF>(buf, readOffset);
					}
					else
					{
						DeserializePacket(member, buf, readOffset);
					}
				}
			});
		}


		/// <summary>
		/// Writes a single POD Data Type into a buffer
		/// </summary>
		/// <typeparam name="Type">Data Type</typeparam>
		/// <param name="buf">reference to target buffer</param>
		/// <param name="data">data</param>
		/// <param name="writeOffset">insertion offset to write</param>
		template<typename Type>
		static void WriteSimpleData(char* buf, Type data, int* writeOffset)
		{
			memcpy(buf + *writeOffset, &data, sizeof(Type));
			*writeOffset = *writeOffset + (sizeof(Type));
		};


		static void WriteVector(char* buf, UnrealTypesEmulator::Vector3D vector, int* writeOffset);

		static void WriteQuaternion(char* buf, UnrealTypesEmulator::Quaternion quat, int* writeOffset);


		/// <summary>
		/// Reads a single POD Data Type into a buffer
		/// </summary>
		/// <typeparam name="Type">Data Type</typeparam>
		/// <param name="buf">reference to target buffer</param>
		/// <param name="readOffset">offset to read data</param>
		/// <returns>read data of specified type</returns>
		template <typename Type>
		static Type ReadSimpleData(char* buf, int* readOffset)
		{
			Type data;

			memcpy(&data, buf + *readOffset, sizeof(Type));
			*readOffset = *readOffset + (sizeof(Type));

			return data;
		};


		static UnrealTypesEmulator::Vector3D ReadVector(char* buf, int* readOffset);

		static UnrealTypesEmulator::Quaternion ReadQuaternion(char* buf, int* readOffset);
	};
}