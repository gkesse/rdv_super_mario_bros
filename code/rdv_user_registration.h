#pragma once

#include "rdv_objects.h"

namespace Ui {
class rdv_user_registration;
}

class rdv_user_registration : public QDialog
{
	Q_OBJECT

public:
	explicit rdv_user_registration(QWidget* _parent = nullptr);
	~rdv_user_registration();

	const rdv_errors& getErrors() const     {return m_errors;}

private slots:
    void on_btnCancel_clicked();
    void on_radPassword_clicked(bool checked);
    void on_btnSubmit_clicked();

private:
	Ui::rdv_user_registration *ui;
	rdv_errors m_errors;
};
