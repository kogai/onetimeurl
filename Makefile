PROJECT_ID := $(shell gcloud config get-value project -q)

.PHONY: app
app:
	docker build -t $(PROJECT_ID)/app:v1 .
	docker tag $(PROJECT_ID)/app:v1 gcr.io/$(PROJECT_ID)/app:v1

.PHONY: create
create:
	kubectl create -f app.yaml
	kubectl create -f db.yaml
	kubectl create -f cache.yaml

.PHONY: delete
delete:
	kubectl delete service --all
	kubectl delete pvc --all
	kubectl delete pod --all
	kubectl delete deploy --all

.PHONY: replace
replace:
	kubectl replace --force -f app.yaml
	kubectl replace --force -f db.yaml
	kubectl replace --force -f cache.yaml
