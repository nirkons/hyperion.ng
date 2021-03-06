#pragma once

#include <utils/Logger.h>

class QUdpSocket;

///
/// @brief The SSDP Server sends and receives (parses) SSDP requests
///
class SSDPServer : public QObject {
	Q_OBJECT

public:
	friend class SSDPHandler;
	///
	/// @brief Construct the server, listen on default ssdp address/port with multicast
	/// @param parent  The parent object
	///
	SSDPServer(QObject* parent = nullptr);
	virtual ~SSDPServer();

	///
	/// @brief Prepare server after thread start
	///
	void initServer();

	///
	/// @brief Start SSDP
	/// @return false if already running or bind failure
	///
	bool start();

	///
	/// @brief Stop SSDP
	///
	void stop();

	///
	/// @brief Send an answer to mSearch requester
	/// @param st         the searchTarget
	/// @param senderIp   Ip address of the sender
	/// @param senderPort The port of the sender
	///
	void sendMSearchResponse(const QString& st, const QString& senderIp, quint16 senderPort);

	///
	/// @brief Send ByeBye notification (on SSDP stop) (repeated 3 times)
	/// @param st        Search target
	///
	void sendByeBye(const QString& st);

	///
	/// @brief Send a NOTIFY msg on SSDP startup to notify our presence (repeated 3 times)
	/// @param st        The search target
	///
	void sendAlive(const QString& st);

	///
	/// @brief Send a NOTIFY msg as ssdp:update to notify about changes
	/// @param st        The search target
	///
	void sendUpdate(const QString& st);

	///
	/// @brief Overwrite description address
	/// @param addr  new address
	///
	void setDescriptionAddress(const QString& addr) { _descAddress = addr; };

	///
	/// @brief Set uuid
	/// @param uuid  The uuid
	///
	void setUuid(const QString& uuid) { _uuid = uuid; };

	///
	/// @brief set new flatbuffer server port
	///
	void setFlatBufPort(quint16 port) { _fbsPort = QString::number(port); };

	///
	/// @brief Get current flatbuffer server port
	///
	quint16 getFlatBufPort() { return _fbsPort.toInt(); };

	///
	/// @brief set new jsonserver server port
	///
	void setJsonServerPort(quint16 port) { _jssPort = QString::number(port); };

	///
	/// @brief get new jsonserver server port
	///
	quint16 getJsonServerPort() { return _jssPort.toInt(); };

		///
	/// @brief set new hyperion name
	///
	void setHyperionName(const QString &name) { _name = name; };

	///
	/// @brief get hyperion name
	///
	QString getHyperionName() { return _name; };


signals:
	///
	/// @brief Emits whenever a new SSDP search "man : ssdp:discover" is received along with the service type
	/// @param target  The ST service type
	/// @param mx      Answer with delay in s
	/// @param address The ip of the caller
	/// @param port    The port of the caller
	///
	void msearchRequestReceived(const QString& target, const QString& mx, const QString address, quint16 port);

private:
	Logger* _log;
	QUdpSocket* _udpSocket;

	QString _serverHeader;
	QString _uuid;
	QString _fbsPort;
	QString _jssPort;
	QString _name;
	QString _descAddress;
	bool    _running;

private slots:
	void readPendingDatagrams();

};
