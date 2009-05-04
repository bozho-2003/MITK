#ifndef QmitkDataStorageTableModel_h
#define QmitkDataStorageTableModel_h

/// Own includes.
#include "mitkDataStorage.h"
#include "mitkBaseProperty.h"
#include "mitkWeakPointer.h"
#include "mitkNodePredicateBase.h"

/// Toolkit includes.
#include <QAbstractTableModel>

/// Forward declarations.

/// 
/// \class QmitkDataStorageTableModel
///
/// \brief A table model for a set of DataTreeNodes defined by a predicate.
/// \TODO make columns interchangeable, select which properties to show as columns
///
class QMITK_EXPORT QmitkDataStorageTableModel : public QAbstractTableModel
{
  Q_OBJECT

  //#Ctors/Dtor
  public:    
    ///
    /// Constructs a new QmitkDataStorageTableModel and sets a predicate that defines
    /// this list.
    /// \see setPredicate()
    ///
    QmitkDataStorageTableModel(mitk::DataStorage::Pointer _DataStorage, mitk::NodePredicateBase* _Predicate = 0
      , QObject* parent = 0 ); 

    ///
    /// Standard dtor. Delete predicate, disconnect from DataStorage.
    ///
    virtual ~QmitkDataStorageTableModel();

  //# Public GETTER
  public:
    ///
    /// Get the DataStorage.
    /// 
    const mitk::DataStorage::Pointer GetDataStorage() const;
    ///
    /// Get the predicate.
    /// 
    mitk::NodePredicateBase::Pointer GetPredicate() const;
    ///
    /// Get node at a specific model index. Another way to implement this, is
    /// by introducing a new role like "DateTreeNode" and capture
    /// that in the data function.
    ///
    mitk::DataTreeNode::Pointer GetNode(const QModelIndex &index) const;
    ///
    /// Overridden from QAbstractTableModel. Returns the header data at section
    /// for given orientation and role. 
    ///
    QVariant headerData(int section, Qt::Orientation orientation,
      int role) const;
    ///
    /// Overridden from QAbstractTableModel. Returns what can be done
    /// with an item.
    ///
    Qt::ItemFlags flags(const QModelIndex &index) const;
    ///
    /// Overridden from QAbstractTableModel. Returns the node count.
    ///
    int rowCount(const QModelIndex &parent) const;
    ///
    /// Overridden from QAbstractTableModel. Returns the number of features (columns) to display.
    ///
    int columnCount(const QModelIndex &parent) const;
    ///
    /// Overridden from QAbstractTableModel. Returns the data at index for given role.
    ///
    QVariant data(const QModelIndex &index, int role) const;

  //# Public SETTERS
  public:
    ///
    /// Sets the DataStorage.
    ///
    void SetDataStorage(mitk::DataStorage::Pointer _DataStorage);
    ///
    /// Sets the predicate. <b>QmitkDataStorageTableModel is owner of the predicate!</b>
    ///
    void SetPredicate(mitk::NodePredicateBase* _Predicate);
    ///
    /// Called when a DataStorage Add Event was thrown. May be reimplemented
    /// by deriving classes.
    ///
    virtual void NodeAdded(const mitk::DataTreeNode* node);
    ///
    /// Called when a DataStorage Remove Event was thrown. May be reimplemented
    /// by deriving classes.
    ///
    virtual void NodeRemoved(const mitk::DataTreeNode* node);
    ///
    /// \brief Called when a single property was changed.
    ///
    virtual void PropertyModified(const itk::Object *caller, const itk::EventObject &event);
    ///
    /// Overridden from QAbstractTableModel. Sets data at index for given role.
    ///
    bool setData(const QModelIndex &index, const QVariant &value,
      int role);

  //#Protected SETTER
  protected:
    ///
    /// Called when DataStorage or Predicate changed. Resets whole model and reads all nodes
    /// in again.
    ///
    virtual void Reset();

  //#Protected MEMBER VARIABLES
  protected:
    ///
    /// Pointer to the DataStorage from which the nodes are selected (remember: in OpenCherry there
    /// might be more than one DataStorage).
    /// Store it in a weak pointer. This is a GUI class which should not hold a strong reference
    /// to any non-GUI Object.
    ///
    mitk::WeakPointer<mitk::DataStorage> m_DataStorage;
    ///
    /// Holds the predicate that defines this SubSet of Nodes. If m_Predicate
    /// is NULL all Nodes will be selected.
    ///
    mitk::NodePredicateBase::Pointer m_Predicate;
    ///
    /// Holds all selected Nodes.
    ///
    mitk::DataStorage::SetOfObjects::Pointer m_NodeSet;
    ///
    /// \brief Maps a property to an observer tag.
    ///
    std::map<mitk::BaseProperty*, unsigned long> m_NamePropertyModifiedObserverTags;
    ///
    /// \brief Maps a property to an observer tag.
    ///
    std::map<mitk::BaseProperty*, unsigned long> m_VisiblePropertyModifiedObserverTags;
    ///
    /// Saves if this model is currently working on events to prevent endless event loops.
    /// 
    bool m_BlockEvents;

};

#endif

